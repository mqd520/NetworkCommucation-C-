#include "stdafx.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/SocketTool.h"
#include "Include/tc/TimerMoudleMgr.h"

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
	LogMgr TcpCommu::logMgr;


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

	SendDataHandler* TcpCommu::GetSendHandler()
	{
		return &sendHandler;
	}

	void OnSocketToolError(string err, void* lpParam)
	{
		TcpCommu::GetLogMgr()->AddLog(ETcpLogType::Err, "%s", err.c_str());
	}
}