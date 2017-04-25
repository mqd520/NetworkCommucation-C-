
// Client2.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "TcpClientT.h"

#define WM_CUSTOM_MESSAGE1	(WM_USER+1)

using namespace NetworkCommunication;


// CClient2App: 
// 有关此类的实现，请参阅 Client2.cpp
//

class CClient2App : public CWinApp
{
public:
	CClient2App();
	CTcpClientT<CClient2App> m_tcp;

	// 重写
public:
	virtual BOOL InitInstance();

protected:
	bool OnRecvData(BYTE buf[], int len);

	bool OnRecvEvt(TcpEvtType type, TCHAR* msg);
	// 实现

	DECLARE_MESSAGE_MAP()
};

extern CClient2App theApp;