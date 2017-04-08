
// Client3.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "TCPClientMgr.h"
#include "DemoPackage.h"
#include "DemoProtocolMgr.h"

using namespace TCPCommunication;

// CClient3App: 
// 有关此类的实现，请参阅 Client3.cpp
//

class CClient3App : public CWinApp
{
public:
	CClient3App();

	// 重写
public:
	virtual BOOL InitInstance();
	CTCPClientMgr<DemoPackageType, DemoPackageBase, CDemoProtocolMgr> m_tcp;//TCP客户端管理对象

	// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CClient3App theApp;