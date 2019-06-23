#include "stdafx.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/SocketTool.h"

namespace tc
{
	volatile bool TcpCommu::m_bExited = false;

	SelectThread TcpCommu::selectThread;
	RecvThread TcpCommu::recvThread;
	SendThread TcpCommu::sendThread;
	TcpEvtThread TcpCommu::tcpEvtThread;

	Select TcpCommu::select;
	RecvDataHandler TcpCommu::recvHandler;

	SocketDataMgr TcpCommu::socketDataMgr;
	TcpConnectionMgr TcpCommu::tcpConnMgr;
	TcpServiceMgr TcpCommu::tcpServiceMgr;
	TcpEvtMgr TcpCommu::tcpEvtMgr;
	LogMgr TcpCommu::logMgr;


	void TcpCommu::Init()
	{
		SocketTool::Init();

		GetSelectThread()->Run();		// 启动select线程
		GetRecvThread()->Run();			// 启动收数据线程
		GetSendThread()->Run();			// 启动发数据线程
		GetTcpEvtThread()->Run();		// 启动事件线程
	}

	void TcpCommu::Exit()
	{
		m_bExited = true;

		recvHandler.Clear();
		tcpEvtMgr.Clear();
		tcpConnMgr.Clear();
		socketDataMgr.Clear();

		GetSelectThread()->Exit();
		GetRecvThread()->Exit();
		GetSendThread()->Exit();
		GetTcpEvtThread()->Exit();

		Sleep(1 * 1000);
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

	RecvDataHandler* TcpCommu::GetRecvHandler()
	{
		return &recvHandler;
	}
}