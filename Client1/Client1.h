
// Client1.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "TcpClient.h"
#include "Timer.h"

using namespace NetworkCommunication;

#define WM_CUSTOM_MESSAGE1	(WM_USER+1)

// CClient1App: 
// 有关此类的实现，请参阅 Client1.cpp
//

//接收数据
bool OnRecvData(BYTE buf[], int len);

class CClient1App : public CWinApp
{
public:
	CClient1App();
	CTcpClient m_tcp;

	// 重写
public:
	virtual BOOL InitInstance();

	// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CClient1App theApp;