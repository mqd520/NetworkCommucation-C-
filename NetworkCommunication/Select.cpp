#include "stdafx.h"
#include "Select.h"
#include "TcpConnectionMgr.h"
#include "Thread.h"
#include "NetCommuMgr.h"
#include "Def.h"
#include "Common.h"

namespace NetworkCommunication
{
	void OnSelectThreadStart();

	CSelect::CSelect() :
		m_bExit(false),
		m_threadSelect(NULL),
		m_selectTimeout({ 0, 0 })
	{

	}

	CSelect::~CSelect()
	{
		if (m_threadSelect)
		{
			delete m_threadSelect;
		}
	}

	void CSelect::AddSocket(SOCKET socket, int type)
	{
		m_vecSocket.push_back({ socket, type });
	}

	void CSelect::Run()
	{
		if (m_threadSelect == NULL)
		{
			m_threadSelect = new CThread();
			m_threadSelect->SetCallback(OnSelectThreadStart);
			m_threadSelect->Start();
		}
	}

	void OnSelectThreadStart()
	{
		PrintfInfo("select thread started");
		CNetworkCommuMgr::GetSelect()->ThreadEntry();
	}

	void CSelect::ThreadEntry()
	{
		StartSelect();
	}

	void CSelect::StartSelect()
	{
		while (true)
		{
			Sleep(2 * 1000);//调试时使用,无意义,可注释掉

			CalcSocketGroup();//对socket进行分组

			if (m_group.size() > 0)
			{
				for (int i = 0; i < (int)m_group.size(); i++)
				{
					FD_ZERO(&m_readSet);

					for (int j = 0; j < (int)m_group[i].size(); j++)
					{
						FD_SET(m_group[i][j].socket, &m_readSet);
					}

					m_socketAPI.Select(0, &m_readSet, NULL, NULL, &m_selectTimeout);
					CNetworkCommuMgr::GetTcp()->OnServerSocketCanRead(m_group[i][0].socket);
					if (m_readSet.fd_count > 0)
					{
						//遍历分组socket，检查socket信号
						for (int k = 0; k < (int)m_group[i].size(); k++)
						{
							SelectSocketData socketData = m_group[i][k];
							CheckSocketSingal(socketData);
						}
					}
				}
			}
			else
			{
				Sleep(10);
			}
		}
	}

	void CSelect::CalcSocketGroup()
	{
		m_group.clear();

		int nSocketCount = (int)m_vecSocket.size();//socket总数
		int nGroupCount = nSocketCount / FD_SETSIZE + (nSocketCount % FD_SETSIZE == 0 ? 0 : 1);//分组数
		for (int i = 0; i < nGroupCount; i++)
		{
			vector<SelectSocketData> vec;
			m_group.push_back(vec);
		}

		//遍历所有socket
		for (int i = 0; i < (int)m_vecSocket.size(); i++)
		{
			int groupIndex = (i + 1) / FD_SETSIZE + ((i + 1) % FD_SETSIZE == 0 ? 0 : 1) - 1;//计算当前socket所在分组索引
			m_group[groupIndex].push_back(m_vecSocket[i]);//将socket填入对应的组中
		}
	}

	void CSelect::CheckSocketSingal(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &m_readSet);
		if (result > 0)
		{
			if (socketData.type == ESelectSocketType::RecvConn)//指示socket用于接收新连接
			{
				CNetworkCommuMgr::GetTcp()->OnServerSocketCanRead(socketData.socket);
			}
			else//指示socket用于读写数据
			{
				CNetworkCommuMgr::GetTcp()->OnReadWriteSocketCanRead(socketData.socket);
			}
		}
	}

	void CSelect::RemoveSocket(SOCKET socket)
	{
		for (vector<SelectSocketData>::iterator it = m_vecSocket.begin(); it < m_vecSocket.end(); it++)
		{
			if (it->socket == socket)
			{
				if (it->type == ESelectSocketType::ReadWriteData)
				{
					m_vecSocket.erase(it);
					//m_socketAPI.CloseSocket(socket);//关闭socket
				}
				else
				{
					m_vecSocket.erase(it);
				}
				break;
			}
		}
	}
}