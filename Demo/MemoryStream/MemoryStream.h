
// MemoryStream.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMemoryStreamApp: 
// �йش����ʵ�֣������ MemoryStream.cpp
//

class CMemoryStreamApp : public CWinApp
{
public:
	CMemoryStreamApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMemoryStreamApp theApp;