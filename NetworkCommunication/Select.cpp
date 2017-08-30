#include "stdafx.h"
#include "Select.h"
#include "TcpConnectionMgr.h"
#include "Thread.h"
#include "NetCommuMgr.h"
#include "Def.h"
#include "Common.h"
#include "NetErrorAction.h"

namespace NetworkCommunication
{
	void OnSelectThreadStart();

	CSelect::CSelect() :
		m_bExit(false),
		m_threadSelect(NULL),
		m_selectTimeout({ 0, 0 }),
		m_nBufLen(TCPRECVBUFFERSIZE)
	{

	}

	CSelect::~CSelect()
	{
		if (m_threadSelect)
		{
			delete m_threadSelect;
		}
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
		PrintfInfo(_T("select thread started"));
		CNetworkCommuMgr::GetSelect()->ThreadEntry();
	}

	void CSelect::ThreadEntry()
	{
		StartSelect();
	}

	void CSelect::AddSocket(SOCKET socket, int type)
	{
		m_vecSocket.push_back({ socket, type });
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
					m_socketAPI.CloseSocket(socket);//关闭socket
				}
				else
				{
					m_vecSocket.erase(it);
				}
				break;
			}
		}
	}

	void CSelect::StartSelect()
	{
		while (true)
		{
			//Sleep(2 * 1000);//调试时使用,无意义,可注释掉

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
		for (int i = 0; i < nSocketCount; i++)
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
				RecvNewConnection(socketData.socket);//接收新连接
			}
			else//指示socket用于读写数据
			{
				RecvPeerData(socketData.socket);
			}
		}
	}

	void CSelect::RecvNewConnection(SOCKET server)
	{
		CTcpServer* pTcpServer = CNetworkCommuMgr::GetTcpServerMgr()->GetTcpServerByServerSocket(server);//获取指定socket关联的tcp server
		if (pTcpServer)
		{
			SOCKET client = m_socketAPI.Accept(server, pTcpServer->GetServerSocketAddr());
			if (client > 0)
			{
				CRecvNewConnAction* pAction = new CRecvNewConnAction(server, client);//创建tcp动作
				CNetworkCommuMgr::GetTcp()->PushTcpAction(pAction);
			}
		}
	}

	void CSelect::RecvPeerData(SOCKET recv)
	{
		BYTE* pBuf = new BYTE[m_nBufLen];
		int len = m_socketAPI.Recv(recv, pBuf, m_nBufLen);
		if (len > 0)//指示接收数据成功
		{
			//创建接收到对端数据动作
			PeerData* pData = new PeerData();
			pData->len = len;
			pData->pBuf = pBuf;
			pData->socket = recv;
			CRecvPeerDataAction* pAction = new CRecvPeerDataAction(pData);
			CNetworkCommuMgr::GetTcp()->PushTcpAction(pAction);
		}
		else
		{
			delete pBuf;
			RemoveSocket(recv);//删除select中指定socket

			if (len == 0)//指示对端主动关闭了连接
			{
				CPeerCloseAction* pAction = new CPeerCloseAction(recv);
				CNetworkCommuMgr::GetTcp()->PushTcpAction(pAction);
			}
			else//指示发生了网络错误
			{
				CNetErrorAction* pAction = new CNetErrorAction(recv);
				CNetworkCommuMgr::GetTcp()->PushTcpAction(pAction);
			}
		}
	}
}