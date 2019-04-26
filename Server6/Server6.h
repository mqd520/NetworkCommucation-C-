
// Server6.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "TcpServer.h"
#include "TcpSessionDataMgr.h"

using namespace NetworkCommunication;

// CServer6App: 
// 有关此类的实现，请参阅 Server6.cpp
//

class CServer6App : public CWinApp
{
public:
	CTcpServer* m_pTcpSrv;//tcp服务端
	CTcpDataSessionDataMgr m_sessionMgr;//tcp会话数据管理

public:
	CServer6App();
	~CServer6App();

	// 重写
public:
	virtual BOOL InitInstance();

	// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CServer6App theApp;