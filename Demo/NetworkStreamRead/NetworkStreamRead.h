
// NetworkStreamRead.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNetworkStreamReadApp: 
// �йش����ʵ�֣������ NetworkStreamRead.cpp
//

class CNetworkStreamReadApp : public CWinApp
{
public:
	CNetworkStreamReadApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNetworkStreamReadApp theApp;