
// Client1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "SocketClient.h"
#include "SocketClientT.h"

using namespace TCPCommunication;

#define WM_CUSTOM_MESSAGE1	(WM_USER+1)

// CClient1App: 
// �йش����ʵ�֣������ Client1.cpp
//

//��������
bool OnRecvData(BYTE buf[], int len);

class CClient1App : public CWinApp
{
protected:
	bool OnRecvDataT(BYTE buf[], int len);

public:
	CClient1App();
	CSocketClient m_socket;
	CSocketClientT<CClient1App>	m_socketT;

	// ��д
public:
	virtual BOOL InitInstance();

	// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CClient1App theApp;