
// Client1.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Client1.h"
#include "Client1Dlg.h"
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

// CClient1App

BEGIN_MESSAGE_MAP(CClient1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CClient1App 构造

CClient1App::CClient1App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CClient1App 对象

CClient1App theApp;


// CClient1App 初始化

BOOL CClient1App::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	LogSrv::Init("Client.exe.Log");

	ExceptionHandler::Init();
	ExceptionHandler::RegExceptionCallback(OnException, &theApp);
	ExceptionHandler::SetFileName("Client1.exe");

	Fun1 fun = std::bind(OnTcpCommLog, _1, _2, _3, _4);
	TcpLogMgr::SetCallbackFn(fun, NULL, NULL);
	TcpCommu::Init();
	srv1.Init();


	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CClient1Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



int CClient1App::ExitInstance()
{
	// TODO:  在此添加专用代码和/或调用基类
	LogSrv::Exit();
	srv1.Exit();
	TcpCommu::Exit();

	return CWinApp::ExitInstance();
}

Service1& CClient1App::GetSrv1()
{
	return srv1;
}

void OnException(void* pParam1, void* pParam2)
{
	LogSrv::Exit();
	TcpCommu::Exit();
}

//************************************
// Method:    TcpComm日志事件处理
// Parameter: int type: 日志类型(ETcpLogType)
// Parameter: string log:	日志内容
// Parameter: void * pParam1
// Parameter: void * pParam2
//************************************
void OnTcpCommLog(ETcpLogType type, string log, void* pParam1, void* pParam2)
{
	//OutputDebugStringA(log.c_str());
	//OutputDebugStringA("\n");

	ELogSrvType type1 = ELogSrvType::Info;
	if (type == ETcpLogType::Warn)
	{
		type1 = ELogSrvType::Warn;
	}
	else if (type == ETcpLogType::Debug)
	{
		type1 = ELogSrvType::Debug;
	}
	else if (type == ETcpLogType::Error)
	{
		type1 = ELogSrvType::Error;
	}
	else if (type == ETcpLogType::Fatal)
	{
		type1 = ELogSrvType::Fatal;
	}

	LogSrv::WriteLine(type1, false, log);

	if (theApp.m_pMainWnd)
	{
		SendMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_LOGINFO, (WPARAM)log.c_str(), NULL);
	}
}
