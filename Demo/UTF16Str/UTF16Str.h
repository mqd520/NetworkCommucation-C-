
// UTF16Str.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUTF16StrApp: 
// �йش����ʵ�֣������ UTF16Str.cpp
//

class CUTF16StrApp : public CWinApp
{
public:
	CUTF16StrApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUTF16StrApp theApp;