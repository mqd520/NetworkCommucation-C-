
// Client3.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "DemoProtocolClient.h"
using namespace DemoProtocolMgr;


#define WM_CUSTOM_MESSAGE1	(WM_USER+1)

// CClient3App: 
// �йش����ʵ�֣������ Client3.cpp
//

class CClient3App : public CWinApp
{
public:
	CClient3App();

	// ��д
public:
	virtual BOOL InitInstance();
	CDemoProtocolClient m_demoProtocol;//demoЭ��������

	// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CClient3App theApp;