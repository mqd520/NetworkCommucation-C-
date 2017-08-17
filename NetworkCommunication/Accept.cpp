#include "stdafx.h"
#include "Accept.h"
#include "NetCommuMgr.h"
#include "TcpConnectionMgr.h"
#include "TcpConnection.h"
#include "AcceptNewConnAction.h"
#include "Common.h"

namespace NetworkCommunication
{
	void OnAcceptThreadStart();

	CAccept::CAccept() :
		m_threadAccept(NULL)
	{

	}

	CAccept::~CAccept()
	{
		if (m_threadAccept)
		{
			delete m_threadAccept;
		}
	}

	void CAccept::OnServerSocketCanRead(SOCKET server)
	{
		ServerSocketData data = CNetworkCommuMgr::GetServerSocketMgr()->GetDataBySocket(server);//��ȡ�����socket��������
		SOCKET client = m_socketAPI.Accept(server, data.addr);
		if (client > 0)
		{
			m_quSocket.push({ server, client });
		}
	}

	void OnAcceptThreadStart()
	{
		Printf1("Accept thread started");
		CNetworkCommuMgr::GetAccept()->ThreadEntry();
	}

	void CAccept::Run()
	{
		if (m_threadAccept == NULL)
		{
			m_threadAccept = new CThread();
			m_threadAccept->SetCallback(OnAcceptThreadStart);
			m_threadAccept->Start();
		}
	}

	void CAccept::ThreadEntry()
	{
		while (true)
		{
			if (m_quSocket.size() > 0)//���в�Ϊ��
			{
				ProcessAcceptQueue();
			}
			else
			{
				Sleep(10);
			}
		}
	}

	void CAccept::ProcessAcceptQueue()
	{
		for (int i = 0; i < (int)m_quSocket.size(); i++)
		{
			SocketPair pair = m_quSocket.front();
			m_quSocket.pop();

			if (FilterClientSocket(pair))
			{
				//����tcp���Ӷ���
				{
					CTcpService* pTcpSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvByLocalSocket(pair.local);//��ȡ����socket������tcp�������
					CTcpConnection* conn = new CTcpConnection(pair.local, pair.peer, pTcpSrv);
					CNetworkCommuMgr::GetTcpConnectionMgr()->PushTcpConn(conn);//����tcp���Ӷ���
				}

				//���������¿ͻ������Ӷ���
				{
					CAcceptNewConnAction* pAction = new CAcceptNewConnAction(pair.local, pair.peer);
					CPeerSocketDataMgr::Create(pair.peer, pair.local);//����������һ���Զ�socket����
					CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpAction(pAction);//����tcp����
				}
			}
		}
	}

	bool CAccept::FilterClientSocket(SocketPair pair)
	{
		bool result = true;

		//ServerSocketRelationData* data = CNetworkCommuMgr::GetServerSocketMgr()->GetDataBySocket(pair.local);//��ȡ�����socket��������

		//_tprintf(_T("Accept a new connection from %s:%d, client: %d \n"), data->ip, data->port, pair.peer);

		return result;
	}
}