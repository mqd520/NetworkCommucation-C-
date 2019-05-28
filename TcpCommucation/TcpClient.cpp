#include "stdafx.h"
#include "TcpClient.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/ConnectSrvResultEvt.h"
#include "MemoryTool.h"

namespace tc
{
	CTcpClient::CTcpClient(TCHAR* strServerIP, int nServerPort) :
		m_bIsConnecting(false),
		m_bIsConnected(false)
	{
		_tcscpy(strServerIP, strServerIP);
		nServerPort = nServerPort;
	}

	CTcpClient::~CTcpClient()
	{

	}

	void CTcpClient::Init()
	{
		if (socket == INVALID_SOCKET)
		{
			socket = m_socketAPI.CreateTcpSocket();
			SOCKADDR_IN addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(nSelfPort);
#ifdef _UNICODE
			string str = UTF8ToMultiByte(strSelfIP);
			addr.sin_addr.S_un.S_addr = inet_addr(str.c_str());
#else
			addr.sin_addr.S_un.S_addr = inet_addr(strSelfIP);
#endif // _UNICODE
			m_socketAPI.SetNonBlock(socket);

			CTcpCommuMgr::GetSelect()->AddSocket(socket, ESelectSocketType::Connect);
		}
	}

	void CTcpClient::Reconnect()
	{
		//没有正在进行连接,没有连接上服务端的时候才能进行连接
		if (!m_bIsConnecting && !m_bIsConnected)
		{
			m_bIsConnecting = true;
			m_socketAPI.Connect1(socket, strSelfIP, nSelfPort);
		}
	}

	void CTcpClient::Connect()
	{
		Init();
		Reconnect();
	}

	bool CTcpClient::Send(BYTE* pBuf, int len, bool asyncs/* = true*/, int* actualLen/* = NULL*/)
	{
		return __super::SendData(socket, pBuf, len, asyncs, actualLen);
	}

	void CTcpClient::OnRecvTcpEvent(TcpEvt* pEvent)
	{
		__super::OnRecvTcpEvent(pEvent);

		if (pEvent->GetEvtType() == ETcpEvt::ConnectSrvResult)
		{
			m_bIsConnecting = false;//连接已完成
			ConnectSrvResultEvt* pConnCmpEvt = (ConnectSrvResultEvt*)pEvent;
			m_bIsConnected = pConnCmpEvt->GetConnectResult(); 
		}
	}
}