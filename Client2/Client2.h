
// Client2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "TcpClientT.h"

#define WM_CUSTOM_MESSAGE1	(WM_USER+1)

using namespace NetworkCommunication;


// CClient2App: 
// �йش����ʵ�֣������ Client2.cpp
//

class CClient2App : public CWinApp
{
public:
	CClient2App();
	CTcpClientT<CClient2App> m_tcp;

	// ��д
public:
	virtual BOOL InitInstance();

protected:
	bool OnRecvData(BYTE buf[], int len);

	bool OnRecvEvt(TcpEvtType type, TCHAR* msg);
	// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CClient2App theApp;