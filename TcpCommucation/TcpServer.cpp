#include "stdafx.h"
#include "Include/tc/TcpServer.h"
#include "Common.h"
#include "TcpConnectionMgr.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "ServerTcpConnection.h"

namespace tc
{
	TcpServer::TcpServer() :
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
			strSelfIP = ip;
			nSelfPort = port;
		}
	}

	bool TcpServer::Listen()
	{
		if (!bListening)
		{
			bListening = true;

			//����select����
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
			TCHAR ip[TC_MAXIPSTRELN];
			int port = 0;
			m_socketAPI.GetPeerIpAndPort(clientSocket, ip, &port);

			bool result = false;//�������ӽ��
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

	void TcpServer::AddAllowIP(TCHAR* ip)
	{
		bool exist = false;
		for (int i = 0; i < (int)m_vecAllowIP.size(); i++)
		{
			if (_tcscmp(m_vecAllowIP[i], ip) == 0)
			{
				exist = true;
				break;
			}
		}
		if (!exist)
		{
			TCHAR* strIP = new TCHAR[TC_MAXIPSTRELN]{0};
			_tcscpy(strIP, ip);
			m_vecAllowIP.push_back(strIP);
		}
	}

	void TcpServer::RemoveAllowIP(TCHAR* ip)
	{
		for (vector<TCHAR*>::iterator it = m_vecAllowIP.begin(); it < m_vecAllowIP.end(); it++)
		{
			if (_tcscmp(*it, ip) == 0)
			{
				m_vecAllowIP.erase(it);
				break;
			}
		}
	}

	void TcpServer::ClearAllowIP()
	{
		m_vecAllowIP.clear();
	}

	bool TcpServer::IsAllow(TCHAR* ip)
	{
		bool result = true;
		int count = (int)m_vecAllowIP.size();
		if (count > 0)
		{
			result = false;
			for (int i = 0; i < count; i++)
			{
				if (_tcscmp(m_vecAllowIP[i], ip) == 0)
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