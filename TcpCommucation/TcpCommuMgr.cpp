#include "stdafx.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/SelectThread.h"
#include "Include/tc/RecvThread.h"
#include "Include/tc/SendThread.h"
#include "Include/tc/TcpEvtThread.h"
#include "Include/tc/Select.h"
#include "Include/tc/RecvDataHandler.h"
#include "Include/tc/SendDataHandler.h"
#include "Include/tc/TcpConnectionMgr.h"
#include "Include/tc/TcpServiceMgr.h"
#include "Include/tc/TcpEvtMgr.h"
#include "Include/tc/SocketDataMgr.h"
#include "Include/tc/SocketTool.h"
#include "Include/tc/TimerMoudleMgr.h"
#include "Include/tc/Log.h"


namespace tc
{
	void OnSocketToolError(string err, void* lpParam);
	void OnTimer(Timer* pTimer, int count, void* pParam1, void* pParam2);


	SelectThread TcpCommu::selectThread;
	RecvThread TcpCommu::recvThread;
	SendThread TcpCommu::sendThread;
	TcpEvtThread TcpCommu::tcpEvtThread;

	Select TcpCommu::select;
	RecvDataHandler TcpCommu::recvHandler;
	SendDataHandler TcpCommu::sendHandler;

	SocketDataMgr TcpCommu::socketDataMgr;
	TcpConnectionMgr TcpCommu::tcpConnMgr;
	TcpServiceMgr TcpCommu::tcpServiceMgr;
	TcpEvtMgr TcpCommu::tcpEvtMgr;

	Timer TcpCommu::t;


	void TcpCommu::Init()
	{
		SocketTool::Init();
		SocketTool::RegErrorCallback(OnSocketToolError, NULL);

		TimerMoudleMgr::Init();

		t.SetTimeout(300);
		t.SetCallback(OnTimer, NULL, NULL);
		t.Run();

		GetSelectThread()->Run();		// 启动select线程
		GetRecvThread()->Run();			// 启动收数据线程
		GetSendThread()->Run();			// 启动发数据线程
		GetTcpEvtThread()->Run();		// 启动事件线程
	}

	void TcpCommu::Exit()
	{
		TimerMoudleMgr::Exit();
		t.Stop();
		TimerMoudleMgr::GetTimerMgr()->Remove(&t);

		socketDataMgr.Clear();
		recvHandler.Clear();
		sendHandler.Clear();
		tcpEvtMgr.Clear();
		tcpConnMgr.Clear();
		tcpServiceMgr.Clear();

		GetSelectThread()->Exit();
		GetRecvThread()->Exit();
		GetSendThread()->Exit();
		GetTcpEvtThread()->Exit();

		Sleep(1 * 1000);

		TcpCommu::GetSocketDataMgr()->ProcessRemovedSocket();
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

	SocketDataMgr* TcpCommu::GetSocketDataMgr()
	{
		return &socketDataMgr;
	}

	RecvDataHandler* TcpCommu::GetRecvHandler()
	{
		return &recvHandler;
	}

	SendDataHandler* TcpCommu::GetSendHandler()
	{
		return &sendHandler;
	}

	void OnSocketToolError(string err, void* lpParam)
	{
		TcpLog::WriteLine(ETcpLogType::Error, true, "%s", err.c_str());
	}

	void OnTimer(Timer* pTimer, int count, void* pParam1, void* pParam2)
	{
		TcpCommu::GetSocketDataMgr()->ProcessRemovedSocket();
	}
}