
// Client3.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Client3.h"
#include "Client3Dlg.h"
#include "Package3.h"

using namespace ProtocolMgr;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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

//���ݻص�
void OnServer3RecvData(Package3Type type, void* data);

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

	m_server3Mgr = new CService3Mgr();
	m_server3Mgr->Init((TCHAR*)_T("192.168.0.15"), 8080, OnServer3RecvData);

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
	delete m_server3Mgr;
	return CWinApp::ExitInstance();
}

void OnServer3RecvData(Package3Type type, void* data)
{
	LPPackage3Base packet = NULL;
	switch (type)
	{
	case Package3Type::type1:
		//SendMessage(NULL, UINT, 0, 0);
		break;
	case Package3Type::type2:
		break;
	case Package3Type::type3:
		break;
	case Package3Type::invalid:
		break;
	default:
		break;
	}
	theApp.m_server3Mgr->ReleasePackage(type, (LPPackage3Base)data);
}
