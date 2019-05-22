#include "stdafx.h"
#include "TcpClient.h"
#include "Include/tc/TcpCommuMgr.h"
#include "ConnectSrvResultEvt.h"
#include "MemoryTool.h"

namespace tc
{
	CTcpClient::CTcpClient(TCHAR* strServerIP, int nServerPort) :
		m_bIsConnecting(false),
		m_bIsConnected(false)
	{
		_tcscpy(m_strServerIP, strServerIP);
		m_nServerPort = nServerPort;
	}

	CTcpClient::~CTcpClient()
	{

	}

	void CTcpClient::Init()
	{
		if (m_socket == INVALID_SOCKET)
		{
			m_socket = m_socketAPI.CreateTcpSocket();
			SOCKADDR_IN addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(m_nServerPort);
#ifdef _UNICODE
			string str = UTF8ToMultiByte(m_strServerIP);
			addr.sin_addr.S_un.S_addr = inet_addr(str.c_str());
#else
			addr.sin_addr.S_un.S_addr = inet_addr(m_strServerIP);
#endif // _UNICODE
			m_socketAPI.SetNonBlock(m_socket);

			CTcpCommuMgr::GetSelect()->AddSocket(m_socket, ESelectSocketType::Connect);
		}
	}

	void CTcpClient::Reconnect()
	{
		//没有正在进行连接,没有连接上服务端的时候才能进行连接
		if (!m_bIsConnecting && !m_bIsConnected)
		{
			m_bIsConnecting = true;
			m_socketAPI.Connect1(m_socket, m_strServerIP, m_nServerPort);
		}
	}

	void CTcpClient::Connect()
	{
		Init();
		Reconnect();
	}

	bool CTcpClient::Send(BYTE* pBuf, int len, bool asyncs/* = true*/, int* actualLen/* = NULL*/)
	{
		return __super::SendData(m_socket, pBuf, len, asyncs, actualLen);
	}

	void CTcpClient::OnRecvTcpEvent(CTcpEvt* pEvent)
	{
		__super::OnRecvTcpEvent(pEvent);

		if (pEvent->GetEvtType() == ETcpEvent::ConnectSrvResult)
		{
			m_bIsConnecting = false;//连接已完成
			CConnectSrvResultEvt* pConnCmpEvt = (CConnectSrvResultEvt*)pEvent;
			m_bIsConnected = pConnCmpEvt->GetConnectResult(); 
		}
	}
}