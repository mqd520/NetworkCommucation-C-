
// GB2312Str.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGB2312StrApp: 
// �йش����ʵ�֣������ GB2312Str.cpp
//

class CGB2312StrApp : public CWinApp
{
public:
	CGB2312StrApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGB2312StrApp theApp;