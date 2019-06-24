
// Server1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Server1.h"
#include "Server1Dlg.h"
#include "afxdialogex.h"
#include "MSG.h"
#include "Def.h"

#include "tc/UTF16Str.h"
#include "tc/GB2312Str.h"

using namespace tc;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServer1Dlg 对话框

CServer1Dlg::CServer1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServer1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServer1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edPort);
	DDX_Control(pDX, IDC_BUTTON1, m_btnListen);
	DDX_Control(pDX, IDC_LIST1, m_lcClients);
	DDX_Control(pDX, IDC_EDIT2, m_edLog);
}

BEGIN_MESSAGE_MAP(CServer1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CServer1Dlg::OnBnClickedButton1)
	ON_MESSAGE(WM_USER_RECVNEWCLIENT, &CServer1Dlg::OnRecvNewClient)
	ON_MESSAGE(WM_USER_CLIENTDISCONN, &CServer1Dlg::OnClientDisconnect)
	ON_MESSAGE(WM_USER_LOGINFO, &CServer1Dlg::OnLog)
	ON_BN_CLICKED(IDC_BUTTON2, &CServer1Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CServer1Dlg 消息处理程序

BOOL CServer1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CString str = _T("8085");
	m_edPort.SetWindowText(str);

	m_lcClients.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_lcClients.InsertColumn(0, _T("No."), LVCFMT_CENTER, 50);
	m_lcClients.InsertColumn(1, _T("Address"), LVCFMT_CENTER, 180);
	m_lcClients.InsertColumn(2, _T("Client Id"), LVCFMT_CENTER, 100);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServer1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServer1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServer1Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码

	m_btnListen.EnableWindow(FALSE);

	CString str;
	m_edPort.GetWindowText(str);
	int port = 0;
	_stscanf_s(str, _T("%d"), &port);
	m_edPort.EnableWindow(FALSE);

	theApp.GetSrv1()->GetMainTcpSrv()->SetListenInfo(SocketTool::GetLocalIP(), port);
	bool b = theApp.GetSrv1()->GetMainTcpSrv()->Listen();

	if (b)
	{
		ShowLog(_T("listen success."));
	}
}

LRESULT CServer1Dlg::OnRecvNewClient(WPARAM wParam, LPARAM lParam)
{
	int id = wParam;

	ClientConnInfo info = theApp.GetSrv1()->GetClientConnInfoMgr()->GetInfo(id);
	if (info.ip != "")
	{
		CString str1;
		str1.Format(_T("%02d"), id + 1);
		CString str2;
		wstring str3 = UTF16Str::FromGB2312(info.ip);
		str2.Format(_T("%s:%d"), str3.c_str(), info.port);
		CString clientId;
		clientId.Format(_T("%d"), info.clientId);

		m_lcClients.InsertItem(id, str1.GetBuffer());
		m_lcClients.SetItemText(id, 1, str2.GetBuffer());
		m_lcClients.SetItemText(id, 2, clientId.GetBuffer());
	}

	return 0;
}

LRESULT CServer1Dlg::OnClientDisconnect(WPARAM wParam, LPARAM lParam)
{
	m_lcClients.DeleteAllItems();

	vector<ClientConnInfo> vec = theApp.GetSrv1()->GetClientConnInfoMgr()->GetAll();
	for (int i = 0; i < (int)vec.size(); i++)
	{
		CString no, addr, clientId;
		no.Format(_T("%02d"), i + 1);
		wstring ip = UTF16Str::FromGB2312(vec[i].ip);
		addr.Format(_T("%s:%d"), ip.c_str(), vec[i].port);
		clientId.Format(_T("%d"), vec[i].clientId);

		m_lcClients.InsertItem(i, no.GetBuffer());
		m_lcClients.SetItemText(i, 1, addr.GetBuffer());
		m_lcClients.SetItemText(i, 2, clientId.GetBuffer());
	}

	return 0;
}

void CServer1Dlg::ShowLog(CString log)
{
	time_t t = time(NULL);
	tm t1;
	localtime_s(&t1, &t);

	CString originLog;
	m_edLog.GetWindowText(originLog);
	CString newLog;
	newLog.Format(_T("[%d-%02d-%02d %02d:%02d:%02d] %s \r\n%s"), t1.tm_year + 1900, t1.tm_mon, t1.tm_mday, t1.tm_hour, t1.tm_min, t1.tm_sec, log.GetString(), originLog.GetString());
	m_edLog.SetWindowText(newLog);
}

LRESULT CServer1Dlg::OnLog(WPARAM wParam, LPARAM lParam)
{
	char* str = (char*)wParam;
	wstring str1 = UTF16Str::FromGB2312(str);
	CString log;
	log.Format(_T("%s"), str1.c_str());
	ShowLog(log);

	return 0;
}

void CServer1Dlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码

	int index = m_lcClients.GetSelectionMark();
	if (index > -1)
	{
		CString addr = m_lcClients.GetItemText(index, 1);
		CString ip;
		int port = 0;
		int index = addr.Find(_T(":"));
		if (index > -1)
		{
			ip = addr.Left(index);
			port = static_cast<int>(stol(addr.Mid(index + 1, addr.GetLength() - index - 1).GetBuffer()));
		}
		string ip1 = GB2312Str::FromUTF16(ip.GetBuffer());

		ClientConnInfo info = theApp.GetSrv1()->GetClientConnInfoMgr()->GetInfo(ip1, port);
		theApp.GetSrv1()->GetClientConnInfoMgr()->Remove(ip1, port);
		theApp.GetSrv1()->GetMainTcpSrv()->CloseClient(info.clientId, true);

		m_lcClients.DeleteItem(index);

		vector<ClientConnInfo> vec = theApp.GetSrv1()->GetClientConnInfoMgr()->GetAll();
		for (int i = 0; i < (int)vec.size(); i++)
		{
			CString no, addr, clientId;
			no.Format(_T("%02d"), i + 1);
			wstring ip = UTF16Str::FromGB2312(vec[i].ip);
			addr.Format(_T("%s:%d"), ip.c_str(), vec[i].port);
			clientId.Format(_T("%d"), vec[i].clientId);

			m_lcClients.InsertItem(i, no.GetBuffer());
			m_lcClients.SetItemText(i, 1, addr.GetBuffer());
			m_lcClients.SetItemText(i, 2, clientId.GetBuffer());
		}
	}
}