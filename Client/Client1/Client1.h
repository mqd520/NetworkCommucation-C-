
// Client1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Service1.h"

// CClient1App: 
// �йش����ʵ�֣������ Client1.cpp
//

class CClient1App : public CWinApp
{
public:
	CClient1App();

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

extern CClient1App theApp;