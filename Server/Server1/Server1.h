
// Server1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "tc/TcpServer.h"

using namespace tc;


// CServer1App: 
// �йش����ʵ�֣������ Server1.cpp
//

class CServer1App : public CWinApp
{
public:
	CServer1App();

protected:
	TcpServer tcpSrv;	// tcp����

public:
	TcpServer* GetTcpSrv();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CServer1App theApp;