#include "stdafx.h"
#include "Select.h"
#include "TcpConnectionMgr.h"
#include "Thread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Def.h"
#include "Common.h"

namespace tc
{
	CSelect::CSelect() :
		m_selectTimeout({ 0, 0 })
	{

	}

	CSelect::~CSelect()
	{

	}

	bool CSelect::IsEmpty()
	{
		m_lock1.Lock();

		bool b = m_vecSocket.size() == 0;

		m_lock1.Unlock();

		return b;
	}

	void CSelect::AddSocket(SOCKET socket, int type)
	{
		m_lock1.Lock();

		m_vecSocket.push_back({ socket, type });

		m_lock1.Unlock();
	}

	void CSelect::RemoveSocket(SOCKET socket, bool close/* = true*/)
	{
		m_lock1.Lock();

		for (vector<SelectSocketData>::iterator it = m_vecSocket.begin(); it != m_vecSocket.end(); it++)
		{
			if (it->socket == socket)
			{
				m_vecSocket.erase(it);
				if (close)
				{
					m_socketAPI.CloseSocket(socket);//关闭socket
				}
				RemoveProcessingSocket(socket);//移除正在处理的socket
				break;
			}
		}

		m_lock1.Unlock();
	}

	void CSelect::Select()
	{
		//Sleep(3 * 1000);	//调试时使用,无意义,可注释掉

		if (CTcpCommuMgr::IsExited())	//指示需要退出了
		{
			return;	//立刻返回
		}

		CalcSocketGroup();//对socket进行分组

		if (m_group.size() > 0)
		{
			//遍历分组集合
			for (int i = 0; i < (int)m_group.size(); i++)
			{
				FD_ZERO(&m_readFdSet);
				FD_ZERO(&m_writeFdSet);
				FD_ZERO(&m_exceptFdSet);

				//遍历分组,将socket分别加入异常集合和读写集合
				for (int j = 0; j < (int)m_group[i].size(); j++)
				{
					FD_SET(m_group[i][j].socket, &m_readFdSet);
					FD_SET(m_group[i][j].socket, &m_writeFdSet);
					FD_SET(m_group[i][j].socket, &m_exceptFdSet);
				}

				m_socketAPI.Select(0, &m_readFdSet, &m_writeFdSet, &m_exceptFdSet, &m_selectTimeout);

				//检查socket的"异常"信号
				if (m_exceptFdSet.fd_count > 0)
				{
					for (int k = 0; k < (int)m_group[i].size(); k++)
					{
						if (CTcpCommuMgr::IsExited())//指示需要退出了
						{
							return;//立刻返回,不再处理后面的队列
						}
						CheckSocketExcept(m_group[i][k]);
					}
				}

				//检查socket的"可读"信号
				if (m_readFdSet.fd_count > 0)
				{
					for (int k = 0; k < (int)m_group[i].size(); k++)
					{
						if (CTcpCommuMgr::IsExited())//指示需要退出了
						{
							return;//立刻返回,不再处理后面的队列
						}
						CheckSocketCanRead(m_group[i][k]);
					}
				}

				//检查socket的"可写"信号
				if (m_writeFdSet.fd_count > 0)
				{
					for (int k = 0; k < (int)m_group[i].size(); k++)
					{
						if (CTcpCommuMgr::IsExited())//指示需要退出了
						{
							return;//立刻返回,不再处理后面的队列
						}
						CheckSocketCanWrite(m_group[i][k]);
					}
				}
			}
		}
	}

	void CSelect::CalcSocketGroup()
	{
		m_lock1.Lock();

		m_group.clear();
		int nSocketCount = (int)m_vecSocket.size();//socket总数
		int nGroupCount = nSocketCount / FD_SETSIZE + (nSocketCount % FD_SETSIZE == 0 ? 0 : 1);//分组数
		for (int i = 0; i < nGroupCount; i++)
		{
			vector<SelectSocketData> vec;
			m_group.push_back(vec);
		}

		//遍历所有socket
		for (int i = 0; i < nSocketCount; i++)
		{
			int groupIndex = (i + 1) / FD_SETSIZE + ((i + 1) % FD_SETSIZE == 0 ? 0 : 1) - 1;//计算当前socket所在分组索引
			m_group[groupIndex].push_back(m_vecSocket[i]);//将socket填入对应的组中
		}

		m_lock1.Unlock();
	}

	bool CSelect::IsProcessingSingal(SOCKET socket, int type)
	{
		m_lock2.Lock();

		bool b = false;//指示当前socket信号是否正在被处理
		for (int i = 0; i < (int)m_vecProcessingData.size(); i++)
		{
			if (m_vecProcessingData[i].socket == socket && m_vecProcessingData[i].type == type)
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			//标记当前socket信号正在被处理
			m_vecProcessingData.push_back({ socket, type });
		}

		m_lock2.Unlock();

		return b;
	}

	void CSelect::CheckSocketExcept(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &m_exceptFdSet);
		if (result > 0)
		{
			//检查socket异常信号是否正在被处理
			if (!IsProcessingSingal(socketData.socket, ESocketSingalType::Except))
			{
				SocketSingalData data = { socketData.socket, ESocketSingalType::Except, socketData.type };
				CTcpCommuMgr::GetOtherSingal()->PushSocket(data);
			}
		}
	}

	void CSelect::CheckSocketCanRead(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &m_readFdSet);
		if (result > 0)
		{
			//检查socket可读信号是否正在被处理
			if (!IsProcessingSingal(socketData.socket, ESocketSingalType::Read))
			{
				SocketSingalData data = { socketData.socket, ESocketSingalType::Read, socketData.type };
				if (socketData.type == ESelectSocketType::Accept)//指示socket用于接收新连接
				{
					CTcpCommuMgr::GetOtherSingal()->PushSocket(data);
				}
				else if (socketData.type == ESelectSocketType::ReadWriteData)//指示socket用于读写数据
				{
					CTcpCommuMgr::GetRecvDataSingal()->PushSocket(data);
				}
			}
		}
	}

	void CSelect::CheckSocketCanWrite(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &m_writeFdSet);
		if (result > 0)
		{
			//检查socket可读信号是否正在被处理
			if (!IsProcessingSingal(socketData.socket, ESocketSingalType::Write))
			{
				SocketSingalData data = { socketData.socket, ESocketSingalType::Write, socketData.type };
				if (socketData.type == ESelectSocketType::ReadWriteData)//指示socket用于读写数据
				{
					CTcpCommuMgr::GetSendDataSingal()->PushSocket(data);
				}
				else if (socketData.type == ESelectSocketType::Connect)//指示socket用于连接服务端
				{
					CTcpCommuMgr::GetOtherSingal()->PushSocket(data);
				}
			}
		}
	}

	void CSelect::OnProcessingSocketCmp(SOCKET socket, int type)
	{
		m_lock2.Lock();

		for (vector<ProcessingSocketData>::iterator it = m_vecProcessingData.begin(); it < m_vecProcessingData.end(); it++)
		{
			if (it->socket == socket && it->type == type)
			{
				m_vecProcessingData.erase(it);
				break;
			}
		}

		m_lock2.Unlock();
	}

	void CSelect::RemoveProcessingSocket(SOCKET socket)
	{
		m_lock2.Lock();

		for (vector<ProcessingSocketData>::iterator it = m_vecProcessingData.begin(); it != m_vecProcessingData.end();)
		{
			if (it->socket == socket)
			{
				it = m_vecProcessingData.erase(it);
			}
			else
			{
				it++;
			}
		}

		m_lock2.Unlock();
	}

	void CSelect::Exit()
	{
		//关闭所有socket
		for (int i = 0; i < (int)m_vecSocket.size(); i++)
		{
			m_socketAPI.CloseSocket(m_vecSocket[i].socket);
		}
	}
}