#include "stdafx.h"
#include "TcpService.h"
#include "Common.h"
#include "NetCommuMgr.h"
#include "ServerTcpConnection.h"
#include "RecvNewConnEvt.h"
#include "RefuseNewConnEvt.h"

namespace tc
{
	CTcpService::CTcpService() :
		m_socket(INVALID_SOCKET),
		m_nServerPort(0),
		m_lpCallback(NULL)
	{
		memset(m_strServerIP, 0, TC_MAXIPSTRELN * sizeof(TCHAR));
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpService(this);
	}

	CTcpService::~CTcpService()
	{

	}

	SOCKET CTcpService::GetSocket()
	{
		return m_socket;
	}

	TCHAR* CTcpService::GetServerIP()
	{
		return m_strServerIP;
	}

	int CTcpService::GetServerPort()
	{
		return m_nServerPort;
	}

	void CTcpService::RegTcpEventCallback(LPTcpEventCallback lpCallback)
	{
		m_lpCallback = lpCallback;
	}

	bool CTcpService::SendData(SOCKET socket, BYTE* pBuf, int len, bool asyncs, int* actualLen)
	{
		//获取指定socket的tcp连接对象
		CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);

		if (pConn)
		{
			if (asyncs)//异步发送
			{
				pConn->SetAsyncSendData(pBuf, len, actualLen);
				return true;
			}
			else//同步发送
			{
				pConn->SendData(pBuf, len, actualLen);
			}
		}

		return false;
	}

	void CTcpService::OnRecvTcpEvent(CTcpEvt* pEvent)
	{
		DispatchTcpEvt(pEvent);
	}

	void CTcpService::DispatchTcpEvt(CTcpEvt* pEvent)
	{
		if (m_lpCallback)
		{
			m_lpCallback(pEvent);//通知事件注册方
		}
	}
}