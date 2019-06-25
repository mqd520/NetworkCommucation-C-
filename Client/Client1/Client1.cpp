
// Client1.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Client1.h"
#include "Client1Dlg.h"
#include "ExceptionHandler.h"
#include "Msg.h"

#include "tc/TcpCommuMgr.h"
using namespace tc;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void OnException(void* pParam1, void* pParam2);
void OnTcpCommLog(ETcpLogType type, string log, void* pParam1, void* pParam2);

// CClient1App

BEGIN_MESSAGE_MAP(CClient1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CClient1App ����

CClient1App::CClient1App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CClient1App ����

CClient1App theApp;


// CClient1App ��ʼ��

BOOL CClient1App::InitInstance()
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

	ExceptionHandler::Init();
	ExceptionHandler::RegExceptionCallback(OnException, &theApp);
	ExceptionHandler::SetFileName("Client1.exe");

	TcpCommu::GetLogMgr()->RegCallback(OnTcpCommLog, &theApp);
	TcpCommu::Init();
	srv1.Init();


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

	CClient1Dlg dlg;
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



int CClient1App::ExitInstance()
{
	// TODO:  �ڴ����ר�ô����/����û���
	srv1.Exit();
	TcpCommu::Exit();

	return CWinApp::ExitInstance();
}

Service1&	CClient1App::GetSrv1()
{
	return srv1;
}

LogSrv&		CClient1App::GetLogSrv()
{
	return logSrv;
}

void OnException(void* pParam1, void* pParam2)
{
	theApp.GetLogSrv().Add("a fatal error has occured, the program will be shut down, please contact the administrator");
}

//************************************
// Method:    TcpComm��־�¼�����
// Parameter: int type: ��־����(ETcpLogType)
// Parameter: string log:	��־����
// Parameter: void * pParam1
// Parameter: void * pParam2
//************************************
void OnTcpCommLog(ETcpLogType type, string log, void* pParam1, void* pParam2)
{
	OutputDebugStringA(log.c_str());
	OutputDebugStringA("\n");

	theApp.GetLogSrv().Add(log);

	if (theApp.m_pMainWnd)
	{
		SendMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_LOGINFO, (WPARAM)log.c_str(), NULL);
	}
}
