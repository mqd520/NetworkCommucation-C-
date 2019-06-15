#include "stdafx.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/SocketTool.h"

namespace tc
{
	volatile bool CTcpCommuMgr::m_bExited = false;

	SelectThread CTcpCommuMgr::selectThread;
	SelectSingalThread CTcpCommuMgr::selectSingalThread;
	RecvThread CTcpCommuMgr::recvThread;
	SendThread CTcpCommuMgr::sendThread;
	TcpEvtThread CTcpCommuMgr::tcpEvtThread;

	Select CTcpCommuMgr::select;
	SelectSingal CTcpCommuMgr::selectSingal;

	SocketDataMgr CTcpCommuMgr::socketDataMgr;
	TcpConnectionMgr CTcpCommuMgr::m_tcpConnMgr;
	TcpServiceMgr CTcpCommuMgr::m_tcpServiceMgr;
	TcpEvtMgr CTcpCommuMgr::m_tcpEvtMgr;
	LogMgr CTcpCommuMgr::logMgr;
	

	void CTcpCommuMgr::Init(LPTcpLogCallback lpfnCallback /*= NULL*/, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		SocketTool::Init();

		if (lpfnCallback != NULL)
		{
			logMgr.RegCallback(lpfnCallback, pParam1, pParam2);
		}

		GetSelectThread()->Run();		// 启动select线程
		GetRecvThread()->Run();			// 启动收数据线程
		GetSendThread()->Run();			// 启动发数据线程
		GetSelectSingalThread()->Run(); // 启动select信号处理线程
		GetTcpEvtThread()->Run();		// 启动tcp事件线程(业务线程)
	}

	void CTcpCommuMgr::Exit()
	{
		m_bExited = true;

		GetSelectThread()->Exit();
		GetRecvThread()->Exit();
		GetSendThread()->Exit();
		GetSelectSingalThread()->Exit();
		GetTcpEvtThread()->Exit();

#if RELEASE
		::Sleep(300);
#endif

		select.Exit();
	}

	bool CTcpCommuMgr::IsExited()
	{
		return m_bExited;
	}

	SelectThread* CTcpCommuMgr::GetSelectThread()
	{
		return &selectThread;
	}

	RecvThread* CTcpCommuMgr::GetRecvThread()
	{
		return &recvThread;
	}

	SendThread* CTcpCommuMgr::GetSendThread()
	{
		return &sendThread;
	}

	SelectSingalThread* CTcpCommuMgr::GetSelectSingalThread()
	{
		return &selectSingalThread;
	}

	TcpEvtThread* CTcpCommuMgr::GetTcpEvtThread()
	{
		return &tcpEvtThread;
	}

	Select* CTcpCommuMgr::GetSelect()
	{
		return &select;
	}

	TcpConnectionMgr* CTcpCommuMgr::GetTcpConnectionMgr()
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

	SocketDataMgr* CTcpCommuMgr::GetSocketDataMgr()
	{
		return &socketDataMgr;
	}

	SelectSingal* CTcpCommuMgr::GetSelectSingal()
	{
		return &selectSingal;
	}
}