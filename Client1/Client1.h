
// Client1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "TcpClient.h"
#include "Timer.h"

using namespace NetworkCommunication;

#define WM_CUSTOM_MESSAGE1	(WM_USER+1)

// CClient1App: 
// �йش����ʵ�֣������ Client1.cpp
//

//��������
bool OnRecvData(BYTE buf[], int len);

class CClient1App : public CWinApp
{
public:
	CClient1App();
	CTcpClient m_tcp;

	// ��д
public:
	virtual BOOL InitInstance();

	// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CClient1App theApp;