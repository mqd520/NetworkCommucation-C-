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

		bool b = vecListenSocket.size() == 0;

		m_lock1.Unlock();

		return b;
	}

	void CSelect::AddSocket(SOCKET socket, int type)
	{
		m_lock1.Lock();

		vecListenSocket.push_back({ socket, type });

		m_lock1.Unlock();
	}

	void CSelect::RemoveSocket(SOCKET socket, bool close/* = true*/)
	{
		m_lock1.Lock();

		for (vector<SelectSocketData>::iterator it = vecListenSocket.begin(); it != vecListenSocket.end(); it++)
		{
			if (it->socket == socket)
			{
				vecListenSocket.erase(it);
				RemoveProcessingSocket(socket);	// 移除正在处理的socket
				
				if (close)
				{
					SocketTool::ShutDown(socket, false);
					SocketTool::CloseSocket(socket, false);
				}

				break;
			}
		}

		m_lock1.Unlock();
	}

	void CSelect::Select()
	{
		//Sleep(1 * 1000);	// 调试时使用,无意义,可注释掉

		if (CTcpCommuMgr::IsExited())	// 指示需要退出了
		{
			return;	// 立刻返回
		}

		CalcSocketGroup();	// 对socket进行分组

		if (groupSocket.size() > 0)
		{
			// 遍历分组集合
			for (int i = 0; i < (int)groupSocket.size(); i++)
			{
				FD_ZERO(&fsRead);
				FD_ZERO(&fsExcept);

				// 遍历分组,将socket分别加入异常集合和读写集合
				for (int j = 0; j < (int)groupSocket[i].size(); j++)
				{
					FD_SET(groupSocket[i][j].socket, &fsRead);
					FD_SET(groupSocket[i][j].socket, &fsExcept);
				}

				SocketTool::Select(0, &fsRead, NULL, &fsExcept, &m_selectTimeout);

				// 检查socket的"异常"信号
				if (fsExcept.fd_count > 0)
				{
					for (int k = 0; k < (int)groupSocket[i].size(); k++)
					{
						if (CTcpCommuMgr::IsExited())	// 指示需要退出了
						{
							return;	//立刻返回, 不再处理后面的队列
						}
						CheckSocketExcept(groupSocket[i][k]);
					}
				}

				// 检查socket的"可读"信号
				if (fsRead.fd_count > 0)
				{
					for (int k = 0; k < (int)groupSocket[i].size(); k++)
					{
						if (CTcpCommuMgr::IsExited())	// 指示需要退出了
						{
							return;	//立刻返回, 不再处理后面的队列
						}
						CheckSocketCanRead(groupSocket[i][k]);
					}
				}
			}
		}
	}

	void CSelect::CalcSocketGroup()
	{
		m_lock1.Lock();

		groupSocket.clear();
		int nSocketCount = (int)vecListenSocket.size();	// socket总数
		int nGroupCount = nSocketCount / FD_SETSIZE + (nSocketCount % FD_SETSIZE == 0 ? 0 : 1);	// 分组数
		for (int i = 0; i < nGroupCount; i++)
		{
			vector<SelectSocketData> vec;
			groupSocket.push_back(vec);
		}

		//遍历所有socket
		for (int i = 0; i < nSocketCount; i++)
		{
			int groupIndex = (i + 1) / FD_SETSIZE + ((i + 1) % FD_SETSIZE == 0 ? 0 : 1) - 1;	// 计算当前socket所在分组索引
			groupSocket[groupIndex].push_back(vecListenSocket[i]);	// 将socket填入对应的组中
		}

		m_lock1.Unlock();
	}

	bool CSelect::IsProcessingSingal(SOCKET socket, int type)
	{
		m_lock2.Lock();

		bool b = false;	// 指示当前socket信号是否正在被处理
		for (int i = 0; i < (int)vecProcessingSocketData.size(); i++)
		{
			if (vecProcessingSocketData[i].socket == socket && vecProcessingSocketData[i].type == type)
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			// 标记当前socket信号正在被处理
			vecProcessingSocketData.push_back({ socket, type });
		}

		m_lock2.Unlock();

		return b;
	}

	void CSelect::CheckSocketExcept(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &fsExcept);
		if (result > 0)
		{
			// 检查socket异常信号是否正在被处理
			if (!IsProcessingSingal(socketData.socket, ESocketSingalType::Except))
			{
				SocketSingalData data = { socketData.socket, ESocketSingalType::Except, socketData.type };
				CTcpCommuMgr::GetOtherSingal()->PushSocket(data);
			}
		}
	}

	void CSelect::CheckSocketCanRead(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &fsRead);
		if (result > 0)
		{
			// 检查socket可读信号是否正在被处理
			if (!IsProcessingSingal(socketData.socket, ESocketSingalType::Read))
			{
				SocketSingalData data = { socketData.socket, ESocketSingalType::Read, socketData.type };
				if (socketData.type == ESocketType::Accept)	// 指示socket用于接收新连接
				{
					CTcpCommuMgr::GetOtherSingal()->PushSocket(data);
				}
				else if (socketData.type == ESocketType::SendRecvData)	// 指示socket用于读写数据
				{
					CTcpCommuMgr::GetRecvDataSingal()->PushSocket(data);
				}
			}
		}
	}

	void CSelect::CheckSocketCanWrite(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &fsWrite);
		if (result > 0)
		{
			// 检查socket可读信号是否正在被处理
			if (!IsProcessingSingal(socketData.socket, ESocketSingalType::Write))
			{
				SocketSingalData data = { socketData.socket, ESocketSingalType::Write, socketData.type };
				if (socketData.type == ESocketType::SendRecvData)	// 指示socket用于读写数据
				{
					CTcpCommuMgr::GetSendDataSingal()->PushSocket(data);
				}
				else if (socketData.type == ESocketType::Connect)		// 指示socket用于连接服务端
				{
					CTcpCommuMgr::GetOtherSingal()->PushSocket(data);
				}
			}
		}
	}

	void CSelect::OnProcessingSocketCmp(SOCKET socket, int type)
	{
		m_lock2.Lock();

		for (vector<ProcessingSocketData>::iterator it = vecProcessingSocketData.begin(); it < vecProcessingSocketData.end(); it++)
		{
			if (it->socket == socket && it->type == type)
			{
				vecProcessingSocketData.erase(it);
				break;
			}
		}

		m_lock2.Unlock();
	}

	void CSelect::RemoveProcessingSocket(SOCKET socket)
	{
		m_lock2.Lock();

		for (vector<ProcessingSocketData>::iterator it = vecProcessingSocketData.begin(); it != vecProcessingSocketData.end();)
		{
			if (it->socket == socket)
			{
				it = vecProcessingSocketData.erase(it);
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
		// 关闭所有socket
		for (int i = 0; i < (int)vecListenSocket.size(); i++)
		{
			SocketTool::ShutDown(vecListenSocket[i].socket, false);
			SocketTool::CloseSocket(vecListenSocket[i].socket, false);
		}
	}
}