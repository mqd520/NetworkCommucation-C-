
// Client1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "SocketClient.h"

using namespace TCPCommunication;

// CClient1App: 
// �йش����ʵ�֣������ Client1.cpp
//

//��������
void OnRecvData(BYTE buf[], int len);

class CClient1App : public CWinApp
{
protected:
	CSocketClient m_socket;

public:
	CClient1App();

	// ��д
public:
	virtual BOOL InitInstance();

	// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CClient1App theApp;