
// Client3.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "ProtocolTool.h"

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

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CClient3App theApp;