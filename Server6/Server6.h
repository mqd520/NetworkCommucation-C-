
// Server6.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "TcpServer.h"
#include "TcpSessionDataMgr.h"

using namespace NetworkCommunication;

// CServer6App: 
// �йش����ʵ�֣������ Server6.cpp
//

class CServer6App : public CWinApp
{
public:
	CTcpServer* m_pTcpSrv;//tcp�����
	CTcpDataSessionDataMgr m_sessionMgr;//tcp�Ự���ݹ���

public:
	CServer6App();
	~CServer6App();

	// ��д
public:
	virtual BOOL InitInstance();

	// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CServer6App theApp;