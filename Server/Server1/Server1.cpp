
// Server1.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Server1.h"
#include "Server1Dlg.h"
#include "MSG.h"
#include "Def.h"
#include "ExceptionHandler.h"

#include "tc/TcpCommuMgr.h"
using namespace tc;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServer1App

BEGIN_MESSAGE_MAP(CServer1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

void OnException(void* pParam1, void* pParam2);
void OnTcpCommLog(int type, string log, void* pParam1, void* pParam2);

// CServer1App ����

CServer1App::CServer1App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CServer1App ����

CServer1App theApp;

// CServer1App ��ʼ��

BOOL CServer1App::InitInstance()
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

	ExceptionHandler::Init();
	ExceptionHandler::SetFileName("Server1.exe");
	ExceptionHandler::RegExceptionCallback(OnException);

	CTcpCommuMgr::Init(OnTcpCommLog, &theApp);
	srv1.Init();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CServer1Dlg dlg;
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

int CServer1App::ExitInstance()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CTcpCommuMgr::Exit();

	return CWinApp::ExitInstance();
}

Service1* CServer1App::GetSrv1()
{
	return &srv1;
}

LogSrv* CServer1App::GetLogSrv()
{
	return &logSrv;
}

void OnException(void* pParam1, void* pParam2)
{
	theApp.GetLogSrv()->Add("a fatal error has occured, the program will be shut down, please contact the administrator");
}

//************************************
// Method:    TcpComm��־�¼�����
// Parameter: int type: ��־����(ELogType)
// Parameter: string log:	��־����
// Parameter: void * pParam1
// Parameter: void * pParam2
//************************************
void OnTcpCommLog(int type, string log, void* pParam1, void* pParam2)
{
	OutputDebugStringA(log.c_str());
	
	theApp.GetLogSrv()->Add(log);
}

