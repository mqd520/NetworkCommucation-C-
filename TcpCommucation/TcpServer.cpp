#include "stdafx.h"
#include "Include/tc/TcpServer.h"
#include "Common.h"
#include "TcpConnectionMgr.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "ServerTcpConnection.h"

namespace tc
{
	TcpServer::TcpServer(string ip /*= ""*/, int port /*= 0*/) :
		TcpService(ip, port),
		bListening(false)
	{

	}

	TcpServer::~TcpServer()
	{

	}

	void TcpServer::SetListenInfo(string ip, int port)
	{
		if (!bListening)
		{
			strIP = ip;
			nPort = port;
		}
	}

	bool TcpServer::Listen()
	{
		if (!bListening)
		{
			bListening = true;

			// ����select����
			CTcpCommuMgr::GetSelect()->AddSocket(socket, ESelectSocketType::Accept);

			return true;
		}

		return true;
	}

	void TcpServer::OnRecvTcpEvent(TcpEvt* pEvent)
	{
		if (pEvent->GetEvtType() == ETcpEvt::RecvNewConn)//�յ�������
		{
			SOCKET clientSocket = pEvent->GetSendRecvSocket();//��ȡ�ͻ���socket
			int port = 0;
			string ip = SocketTool::GetPeerIpAndPort(clientSocket, &port);

			bool result = false;	// �������ӽ��
			if (IsAllow(ip))
			{
				DispatchTcpEvt(pEvent);

				//CRecvNewConnEvt* pRecvEvent = (CRecvNewConnEvt*)pEvent;
				//if (pRecvEvent->m_bRefuse)//�û��ܾ���������
				//{
				//	m_socketAPI.CloseSocket(pRecvEvent->GetSendRecvSocket());//�رտͻ���socket

				//	PrintfInfo(_T("[%s:%d][socket: %d] refuse a new connection [%s:%d][socket: %d]"),
				//		this->GetServerIP(), this->GetServerPort(), this->GetSocket(), ip, port, clientSocket);
				//}
				//else//�û�������������
				//{
				//	//����tcp���Ӷ���
				//	CServerTcpConnection* conn = new CServerTcpConnection(this, pRecvEvent->GetSendRecvSocket(), m_socket);
				//	CTcpCommuMgr::GetTcpConnectionMgr()->PushTcpConn(conn);//����tcp���Ӷ���
				//	result = true;
				//}
			}
			else
			{
				//...
			}

			//CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new RecvNewConnEvt(this, clientSocket, ip, port));

			return;
		}

		__super::OnRecvTcpEvent(pEvent);
	}

	void TcpServer::AddAllowIP(string ip)
	{
		bool exist = false;

		for (int i = 0; i < (int)vecAllowIP.size(); i++)
		{
			if (vecAllowIP[i] == ip)
			{
				exist = true;
				break;
			}
		}

		if (!exist)
		{
			vecAllowIP.push_back(ip);
		}
	}

	void TcpServer::RemoveAllowIP(string ip)
	{
		for (vector<string>::iterator it = vecAllowIP.begin(); it < vecAllowIP.end(); it++)
		{
			if (*it == ip)
			{
				vecAllowIP.erase(it);
				break;
			}
		}
	}

	void TcpServer::ClearAllowIP()
	{
		vecAllowIP.clear();
	}

	bool TcpServer::IsAllow(string ip)
	{
		bool result = true;
		int count = (int)vecAllowIP.size();
		if (count > 0)
		{
			result = false;
			for (int i = 0; i < count; i++)
			{
				if (vecAllowIP[i] == ip)
				{
					result = true;
					break;
				}
			}
		}
		return result;
	}

	bool TcpServer::Send(SOCKET socket, BYTE* pBuf, int len, bool asyncs, int* actualLen)
	{
		return __super::SendData(socket, pBuf, len, asyncs, actualLen);
	}

	void TcpServer::CloseClient(SOCKET client)
	{
		CTcpConnection* pConn = CTcpCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(client);
		if (pConn)
		{
			pConn->Close();
		}
	}
}