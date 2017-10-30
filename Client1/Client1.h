
// Client1.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "TcpClient.h"

using namespace NetworkCommunication;

#define WM_CUSTOM_MESSAGE1	(WM_USER+1)

// CClient1App: 
// 有关此类的实现，请参阅 Client1.cpp
//

class CClient1App : public CWinApp
{
public:
	CTcpClient* m_pTcpClient;

public:
	CClient1App();

	// 重写
public:
	virtual BOOL InitInstance();

	// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CClient1App theApp;