
// NetworkStreamWrite.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNetworkStreamWriteApp: 
// �йش����ʵ�֣������ NetworkStreamWrite.cpp
//

class CNetworkStreamWriteApp : public CWinApp
{
public:
	CNetworkStreamWriteApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNetworkStreamWriteApp theApp;