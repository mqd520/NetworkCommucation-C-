
// Client2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Service1.h"


// CClient2App: 
// �йش����ʵ�֣������ Client2.cpp
//

class CClient2App : public CWinApp
{
public:
	CClient2App();

private:
	Service1	srv1;		// srv1

public:
	//************************************
	// Method:    ��ȡsrv1
	//************************************
	Service1&	GetSrv1();

	// ��д
public:
	virtual BOOL InitInstance();

	// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CClient2App theApp;