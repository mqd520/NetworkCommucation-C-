
// Server1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Service1.h"
#include "LogSrv.h"


// CServer1App: 
// �йش����ʵ�֣������ Server1.cpp
//

class CServer1App : public CWinApp
{
public:
	CServer1App();

protected:
	Service1 srv1;
	LogSrv logSrv;

public:
	Service1* GetSrv1();

	LogSrv* GetLogSrv();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CServer1App theApp;