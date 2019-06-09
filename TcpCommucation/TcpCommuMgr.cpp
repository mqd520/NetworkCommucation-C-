#include "stdafx.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/SocketTool.h"

namespace tc
{
	volatile bool CTcpCommuMgr::m_bExited = false;

	CSelectThread CTcpCommuMgr::m_selectThread;
	CRecvThread CTcpCommuMgr::m_recvThread;
	CSendThread CTcpCommuMgr::m_sendThread;
	CCommonThread CTcpCommuMgr::m_commonThread;
	CTcpEvtThread CTcpCommuMgr::m_tcpEvtThread;

	CSelect CTcpCommuMgr::m_Select;
	SocketSingalProcess CTcpCommuMgr::m_otherSingal;
	SocketSingalProcess CTcpCommuMgr::m_recvSingal;
	SocketSingalProcess CTcpCommuMgr::m_sendSingal;

	CTcpConnectionMgr CTcpCommuMgr::m_tcpConnMgr;
	TcpServiceMgr CTcpCommuMgr::m_tcpServiceMgr;
	TcpEvtMgr CTcpCommuMgr::m_tcpEvtMgr;
	LogMgr CTcpCommuMgr::logMgr;

	void CTcpCommuMgr::Init(LPLogCallback lpfnCallback /*= NULL*/, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		SocketTool::Init();

		if (lpfnCallback != NULL)
		{
			logMgr.RegCallback(lpfnCallback, pParam1, pParam2);
		}

		GetSelectThread()->Run();//启动select线程
		GetRecvThread()->Run();//启动收数据线程
		GetSendThread()->Run();//启动发送数据线程
		GetCommonThread()->Run();//启动通用信号处理线程
		GetTcpEvtThread()->Run();//启动tcp事件线程
	}

	void CTcpCommuMgr::Exit()
	{
		m_bExited = true;

		//退出线程
		GetSelectThread()->Exit();
		GetRecvThread()->Exit();
		GetSendThread()->Exit();
		GetCommonThread()->Exit();
		GetTcpEvtThread()->Exit();

#if RELEASE
		::Sleep(300);
#endif

		m_Select.Exit();
	}

	bool CTcpCommuMgr::IsExited()
	{
		return m_bExited;
	}

	CSelectThread* CTcpCommuMgr::GetSelectThread()
	{
		return &m_selectThread;
	}

	CRecvThread* CTcpCommuMgr::GetRecvThread()
	{
		return &m_recvThread;
	}

	CSendThread* CTcpCommuMgr::GetSendThread()
	{
		return &m_sendThread;
	}

	CCommonThread* CTcpCommuMgr::GetCommonThread()
	{
		return &m_commonThread;
	}

	CTcpEvtThread* CTcpCommuMgr::GetTcpEvtThread()
	{
		return &m_tcpEvtThread;
	}

	CSelect* CTcpCommuMgr::GetSelect()
	{
		return &m_Select;
	}

	SocketSingalProcess* CTcpCommuMgr::GetRecvDataSingal()
	{
		return &m_recvSingal;
	}

	SocketSingalProcess* CTcpCommuMgr::GetSendDataSingal()
	{
		return &m_sendSingal;
	}

	SocketSingalProcess* CTcpCommuMgr::GetOtherSingal()
	{
		return &m_otherSingal;
	}

	CTcpConnectionMgr* CTcpCommuMgr::GetTcpConnectionMgr()
	{
		return &m_tcpConnMgr;
	}

	TcpServiceMgr* CTcpCommuMgr::GetTcpServiceMgr()
	{
		return &m_tcpServiceMgr;
	}

	TcpEvtMgr* CTcpCommuMgr::GetTcpEvtMgr()
	{
		return &m_tcpEvtMgr;
	}

	LogMgr* CTcpCommuMgr::GetLogMgr()
	{
		return &logMgr;
	}
}