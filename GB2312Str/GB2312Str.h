
// GB2312Str.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CGB2312StrApp: 
// 有关此类的实现，请参阅 GB2312Str.cpp
//

class CGB2312StrApp : public CWinApp
{
public:
	CGB2312StrApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CGB2312StrApp theApp;