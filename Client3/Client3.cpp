
// Client3.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Client3.h"
#include "Client3Dlg.h"
#include "NetworkStream.h"
#include "DemoPacket.h"
using namespace DemoProtocolMgr;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//收到包数据处理
void OnRecvPacket(int cmd, BYTE* buf, int len);
//收到事件处理
void OnRecvEvt(CProtocolClientMgr::ProtocolEvtType type, TCHAR* msg);

// CClient3App

BEGIN_MESSAGE_MAP(CClient3App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CClient3App 构造

CClient3App::CClient3App()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CClient3App 对象

CClient3App theApp;


// CClient3App 初始化

BOOL CClient3App::InitInstance()
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


	TCHAR ip[20];
	if (GetLocalIP(ip))
	{
		//m_demoProtocol.Init(ip, 8080, OnRecvPackage, OnRecvEvt);
		m_demoProtocol.Init(_T("192.168.0.113"), 7000, OnRecvPacket, OnRecvEvt);
		m_demoProtocol.Connect();
	}

	CClient3Dlg dlg;
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

int CClient3App::ExitInstance()
{
	// TODO:  在此添加专用代码和/或调用基类
	return CWinApp::ExitInstance();
}

void OnRecvPacket(int cmd, BYTE* buf, int len)
{
	//SendMessage(theApp.m_pMainWnd->m_hWnd, WM_CUSTOM_MESSAGE1, (WPARAM)(int)type, (LPARAM)data);
	if (cmd == DemoPacketCmd::DealerLoginResult)
	{
		DealerLoginResultPack pack;
		pack.Write(buf, len);
		int n1 = pack.nTableID;
	}
	delete buf;
}

void OnRecvEvt(CProtocolClientMgr::ProtocolEvtType type, TCHAR* msg)
{
	if (type == CProtocolClientMgr::ProtocolEvtType::LoginServerSuccess)//登陆服务器成功
	{
		DealerLoginPack pack;
		pack.strPwd = L"123456";
		pack.strName = L"30001";
		pack.nTableID = 0;
		vector<wchar_t*> vec;
		vec.push_back(L"44-6D-57-B6-32-8D");
		pack.vecMac = vec;
		pack.DealerSSID = 0;
		bool b = theApp.m_demoProtocol.SendPack(&pack);
	}
	OutputDebugString(msg);
}