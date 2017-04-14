
// Client3.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Client3.h"
#include "Client3Dlg.h"
#include "NetTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//�յ�DemoPackage�¼�����
void OnRecvDemoPackage(DemoPackageType type, void* data);
//�յ�֪ͨ�¼�
bool OnRecvNotifyEvt(TcpClientEvtType type, TCHAR* msg);

// CClient3App

BEGIN_MESSAGE_MAP(CClient3App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CClient3App ����

CClient3App::CClient3App()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CClient3App ����

CClient3App theApp;


// CClient3App ��ʼ��

BOOL CClient3App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


	TCHAR ip[20];
	if (GetLocalIP(ip))
	{
		m_demoProtocol.Init(ip, 8080, OnRecvDemoPackage, OnRecvNotifyEvt);
	}

	CClient3Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CClient3App::ExitInstance()
{
	// TODO:  �ڴ����ר�ô����/����û���
	return CWinApp::ExitInstance();
}

void OnRecvDemoPackage(DemoPackageType type, void* data)
{
	LPDemoPackageBase packet = NULL;
	SendMessage(theApp.m_pMainWnd->m_hWnd, WM_CUSTOM_MESSAGE1, (WPARAM)(int)type, (LPARAM)data);
	theApp.m_demoProtocol.ReleasePackage(type, (LPDemoPackageBase)data);
}

bool OnRecvNotifyEvt(TcpClientEvtType type, TCHAR* msg)
{
	TRACE(msg);
	return true;
}