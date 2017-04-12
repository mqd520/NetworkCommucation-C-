
// Client3.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "TCPClientMgr.h"
#include "DemoPackage.h"
#include "DemoProtocolMgr.h"

using namespace NetworkCommunication;

// CClient3App: 
// �йش����ʵ�֣������ Client3.cpp
//

class CClient3App : public CWinApp
{
protected:
	void OnRecvData(BYTE buf[], int len);

public:
	CClient3App();

	// ��д
public:
	virtual BOOL InitInstance();
	CTCPClientMgr<DemoPackageType, DemoPackageBase, CDemoProtocolMgr> m_tcp;//TCP�ͻ��˹������
	CSocketClient client;

	// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CClient3App theApp;