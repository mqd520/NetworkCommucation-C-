#include "stdafx.h"
#include "TcpService.h"
#include "Common.h"
#include "Include/tc/TcpCommuMgr.h"
#include "ServerTcpConnection.h"
#include "Include/tc/RecvNewConnEvt.h"

namespace tc
{
	CTcpService::CTcpService() :
		m_socket(INVALID_SOCKET),
		m_nServerPort(0),
		m_lpCallback(NULL)
	{
		memset(m_strServerIP, 0, TC_MAXIPSTRELN * sizeof(TCHAR));
		CTcpCommuMgr::GetTcpServiceMgr()->PushTcpService(this);
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

	void CTcpService::RegTcpEventCallback(LPTcpEventCallback lpCallback, void* param)
	{
		m_lpCallback = lpCallback;
		pParam = param;
	}

	bool CTcpService::SendData(SOCKET socket, BYTE* pBuf, int len, bool asyncs, int* actualLen)
	{
		//获取指定socket的tcp连接对象
		CTcpConnection* pConn = CTcpCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);

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

	void CTcpService::OnRecvTcpEvent(TcpEvt* pEvent)
	{
		DispatchTcpEvt(pEvent);
	}

	void CTcpService::DispatchTcpEvt(TcpEvt* pEvent)
	{
		if (m_lpCallback)
		{
			m_lpCallback(pEvent, pParam);	//通知事件注册方
		}
	}
}