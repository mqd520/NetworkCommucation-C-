
// Server6.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Server6.h"
#include "Server6Dlg.h"
#include "NetCommuMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//************************************
// Method:    tcp�¼�����
// Parameter: tcp����
//************************************
void OnRecvTcpEvent(CTcpAction* pAction);

// CServer6App

BEGIN_MESSAGE_MAP(CServer6App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CServer6App ����

CServer6App::CServer6App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CServer6App ����

CServer6App theApp;


// CServer6App ��ʼ��

BOOL CServer6App::InitInstance()
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

	CNetworkCommuMgr::Init();//��ʼ������ͨ��
	m_tcpSrv.RegTcpEventCallback(OnRecvTcpEvent);//ע��tcp�¼��ص�


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



	CServer6Dlg dlg;
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



int CServer6App::ExitInstance()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CNetworkCommuMgr::Exit();

	return CWinApp::ExitInstance();
}

void OnRecvTcpEvent(CTcpAction* pAction)
{
	switch (pAction->GetActionType())
	{
	case ETcpActionType::RecvNewConnection:
		CRecvNewConnAction* pRecvAction = (CRecvNewConnAction*)pAction;
		int index = theApp.m_sessionMgr.Push({ 0, pRecvAction->GetSendRecvSocket(), _T("192.168.0.68"), 8080 });
		TRACE(_T("recv as new connection: %s:%d, socket: %d"), _T("192.168.0.68"), 8080, pRecvAction->GetSendRecvSocket());
		PostMessage(theApp.m_pMainWnd->m_hWnd, WM_RECVNEWCONNECTION, index, 0);
		break;
	}
}
