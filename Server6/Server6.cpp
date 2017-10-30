
// Server6.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Server6.h"
#include "Server6Dlg.h"
#include "NetCommuMgr.h"
#include "RecvNewConnEvt.h"
#include "RecvPeerDataEvt.h"
#include "RecvConnResultEvt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//************************************
// Method:    tcp事件处理
// Parameter: tcp事件
//************************************
void OnRecvTcpEvent(CTcpEvt* pEvent);

// CServer6App

BEGIN_MESSAGE_MAP(CServer6App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CServer6App 构造

CServer6App::CServer6App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CServer6App 对象

CServer6App theApp;

// CServer6App 初始化

BOOL CServer6App::InitInstance()
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

	m_pTcpSrv = new CTcpServer();
	CNetworkCommuMgr::Init();//初始化网络通信
	m_pTcpSrv->RegTcpEventCallback(OnRecvTcpEvent);//注册tcp事件回调

	CServer6Dlg dlg;
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

int CServer6App::ExitInstance()
{
	// TODO:  在此添加专用代码和/或调用基类
	CNetworkCommuMgr::Exit();

	return CWinApp::ExitInstance();
}

void OnRecvTcpEvent(CTcpEvt* pEvent)
{
	CSocketAPI api;
	TCHAR ip[20];
	int port = 0;
	api.GetPeerIpAndPort(pEvent->GetSendRecvSocket(), ip, &port);

	switch (pEvent->GetEvtType())
	{
	case ETcpEvent::RecvNewConnection://收到新连接
	{
		CRecvNewConnEvt* pRecvEvent = (CRecvNewConnEvt*)pEvent;

		//pRecvEvent->m_bRefuse = true;
		//return;

		//if (_tcscmp(ip, _T("192.168.0.2")) == 0)
		//{
		//	pRecvEvent->m_bRefuse = true;
		//	return;
		//}
	}
	break;
	case ETcpEvent::RecvConnResult://接收新连接结果
	{
		CRecvConnResultEvt* pRecvResultEvt = (CRecvConnResultEvt*)pEvent;
		if (pRecvResultEvt->GetRecvResult())
		{
			TcpSessionData data;
			data.server = theApp.m_pTcpSrv->GetSocket();
			data.client = pRecvResultEvt->GetSendRecvSocket();
			_tcscpy(data.ip, ip);
			data.port = port;
			int index = theApp.m_sessionMgr.Push(data);
			PostMessage(theApp.m_pMainWnd->m_hWnd, WM_RECVNEWCONNECTION, index, 0);
		}
		else
		{
			SendMessage(theApp.m_pMainWnd->m_hWnd, WM_REFUSENEWCONNECTION, (WPARAM)pRecvResultEvt->GetClientIP(), pRecvResultEvt->GetClientPort());
		}
	}
	break;
	case  ETcpEvent::RecvPeerData://收到对端数据
	{
		CRecvPeerDataEvt* pRecvPeerDataEvt = (CRecvPeerDataEvt*)pEvent;
		PeerData* pData = new PeerData();
		pData->buf = pRecvPeerDataEvt->GetRecvBuf();
		pData->len = pRecvPeerDataEvt->GetBufLen();
		_tcscpy(pData->ip, ip);
		pData->port = port;
		SendMessage(theApp.m_pMainWnd->m_hWnd, WM_RECVPEERDATA, (WPARAM)pData, 0);
		delete pData;
	}
	break;
	case ETcpEvent::ConnDisconnect://连接断开
	{
		int index = theApp.m_sessionMgr.RemoveByClientSocket(pEvent->GetSendRecvSocket());
		SendMessage(theApp.m_pMainWnd->m_hWnd, WM_PEERCLOSE, (WPARAM)index, NULL);
	}
	break;
	case  ETcpEvent::AsyncSendDataResult://异步发送结果
	{

	}
	break;
	}
}
