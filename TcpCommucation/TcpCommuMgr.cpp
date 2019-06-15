#include "stdafx.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/SocketTool.h"

namespace tc
{
	volatile bool TcpCommu::m_bExited = false;

	SelectThread TcpCommu::selectThread;
	SelectSingalThread TcpCommu::selectSingalThread;
	RecvThread TcpCommu::recvThread;
	SendThread TcpCommu::sendThread;
	TcpEvtThread TcpCommu::tcpEvtThread;

	Select TcpCommu::select;
	SelectSingal TcpCommu::selectSingal;

	SocketDataMgr TcpCommu::socketDataMgr;
	TcpConnectionMgr TcpCommu::tcpConnMgr;
	TcpServiceMgr TcpCommu::tcpServiceMgr;
	TcpEvtMgr TcpCommu::tcpEvtMgr;
	LogMgr TcpCommu::logMgr;
	

	void TcpCommu::Init()
	{
		SocketTool::Init();

		GetSelectThread()->Run();		// 启动select线程
		GetSelectSingalThread()->Run(); // 启动select信号处理线程
		GetRecvThread()->Run();			// 启动收数据线程
		GetSendThread()->Run();			// 启动发数据线程
		GetTcpEvtThread()->Run();		// 启动tcp事件线程(业务线程)
	}

	void TcpCommu::Exit()
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

	bool TcpCommu::IsExited()
	{
		return m_bExited;
	}

	SelectThread* TcpCommu::GetSelectThread()
	{
		return &selectThread;
	}

	RecvThread* TcpCommu::GetRecvThread()
	{
		return &recvThread;
	}

	SendThread* TcpCommu::GetSendThread()
	{
		return &sendThread;
	}

	SelectSingalThread* TcpCommu::GetSelectSingalThread()
	{
		return &selectSingalThread;
	}

	TcpEvtThread* TcpCommu::GetTcpEvtThread()
	{
		return &tcpEvtThread;
	}

	Select* TcpCommu::GetSelect()
	{
		return &select;
	}

	TcpConnectionMgr* TcpCommu::GetTcpConnectionMgr()
	{
		return &tcpConnMgr;
	}

	TcpServiceMgr* TcpCommu::GetTcpServiceMgr()
	{
		return &tcpServiceMgr;
	}

	TcpEvtMgr* TcpCommu::GetTcpEvtMgr()
	{
		return &tcpEvtMgr;
	}

	LogMgr* TcpCommu::GetLogMgr()
	{
		return &logMgr;
	}

	SocketDataMgr* TcpCommu::GetSocketDataMgr()
	{
		return &socketDataMgr;
	}

	SelectSingal* TcpCommu::GetSelectSingal()
	{
		return &selectSingal;
	}
}