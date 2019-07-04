
// Server2.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Server2.h"
#include "Server2Dlg.h"
#include "ExceptionHandler.h"
#include "Msg.h"

#include "log/LogSrv.h"
using namespace llog;

#include "tc/TcpCommuMgr.h"
#include "tc/TcpLogMgr.h"
using namespace tc;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void OnException(void* pParam1, void* pParam2);
void OnTcpCommLog(ETcpLogType type, string log, void* pParam1, void* pParam2);


// CServer2App

BEGIN_MESSAGE_MAP(CServer2App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CServer2App ����

CServer2App::CServer2App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CServer2App ����

CServer2App theApp;


// CServer2App ��ʼ��

BOOL CServer2App::InitInstance()
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


	LogSrv::Init("Client.exe.Log");

	ExceptionHandler::Init();
	ExceptionHandler::RegExceptionCallback(OnException, &theApp);
	ExceptionHandler::SetFileName("Client2.exe");

	Fun1 fun = std::bind(OnTcpCommLog, _1, _2, _3, _4);
	TcpLogMgr::SetCallbackFn(fun, NULL, NULL);
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

	CServer2Dlg dlg;
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

Service1& CServer2App::GetSrv1()
{
	return srv1;
}

int CServer2App::ExitInstance()
{
	// TODO:  �ڴ����ר�ô����/����û���
	srv1.Exit();
	TcpCommu::Exit();
	LogSrv::Exit();

	return CWinApp::ExitInstance();
}

void OnException(void* pParam1, void* pParam2)
{
	LogSrv::Exit();
	TcpCommu::Exit();
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
	//OutputDebugStringA(log.c_str());
	//OutputDebugStringA("\n");

	theApp.GetSrv1().WriteLog(type, log);
}