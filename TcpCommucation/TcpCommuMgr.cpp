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
#include "Include/tc/TcpLog.h"

namespace tc
{
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


	void OnSocketToolError(string err, void* lpParam);

	void TcpCommu::Init()
	{
		SocketTool::Init();
		SocketTool::RegErrorCallback(OnSocketToolError, NULL);

		TimerMoudleMgr::Init();

		GetSelectThread()->Run();		// 启动select线程
		GetRecvThread()->Run();			// 启动收数据线程
		GetSendThread()->Run();			// 启动发数据线程
		GetTcpEvtThread()->Run();		// 启动事件线程
	}

	void TcpCommu::Exit()
	{
		socketDataMgr.Clear();
		recvHandler.Clear();
		sendHandler.Clear();
		tcpEvtMgr.Clear();
		tcpConnMgr.Clear();
		tcpServiceMgr.Clear();

		TimerMoudleMgr::Exit();

		GetSelectThread()->Exit();
		GetRecvThread()->Exit();
		GetSendThread()->Exit();
		GetTcpEvtThread()->Exit();

		Sleep(1 * 1000);
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
		TcpLog::WriteLine(ETcpLogType::Error, "%s", err.c_str());
	}
}