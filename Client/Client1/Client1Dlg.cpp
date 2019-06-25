
// Client1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client1.h"
#include "Client1Dlg.h"
#include "afxdialogex.h"
#include "Msg.h"

#include "tc/SocketTool.h"
#include "tc/UTF16Str.h"
#include "tc/GB2312Str.h"
using namespace tc;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClient1Dlg 对话框



CClient1Dlg::CClient1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClient1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClient1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edIp);
	DDX_Control(pDX, IDC_EDIT2, m_edPort);
	DDX_Control(pDX, IDC_BUTTON1, m_btnConnect);
	DDX_Control(pDX, IDC_BUTTON2, m_btnClose);
	DDX_Control(pDX, IDC_EDIT3, m_edLog);
}

BEGIN_MESSAGE_MAP(CClient1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_USER_LOGINFO, &CClient1Dlg::OnLog)
	ON_MESSAGE(WM_USER_CONNECTRESULT, &CClient1Dlg::OnConnectResult)
	ON_BN_CLICKED(IDC_BUTTON1, &CClient1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClient1Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CClient1Dlg 消息处理程序

BOOL CClient1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	string strIp = SocketTool::GetLocalIP();
	wstring strIp1 = UTF16Str::FromGB2312(strIp);
	m_edIp.SetWindowText(strIp1.c_str());
	m_edPort.SetWindowText(_T("8085"));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClient1Dlg::OnPaint()
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
HCURSOR CClient1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CClient1Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}

void CClient1Dlg::ShowLog(CString log)
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

LRESULT CClient1Dlg::OnLog(WPARAM wParam, LPARAM lParam)
{
	char* str = (char*)wParam;
	wstring str1 = UTF16Str::FromGB2312(str);
	CString log;
	log.Format(_T("%s"), str1.c_str());
	ShowLog(log);

	return 0;
}

LRESULT CClient1Dlg::OnConnectResult(WPARAM wParam, LPARAM lParam)
{
	bool connected = wParam > 0 ? true : false;
	if (!connected)
	{
		m_btnConnect.EnableWindow(TRUE);
		m_edIp.EnableWindow(TRUE);
		m_edPort.EnableWindow(TRUE);
	}

	return 0;
}

void CClient1Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_btnConnect.EnableWindow(FALSE);
	m_edIp.EnableWindow(FALSE);
	m_edPort.EnableWindow(FALSE);

	CString str;
	m_edPort.GetWindowText(str);
	int port = 0;
	_stscanf_s(str, _T("%d"), &port);
	m_edPort.EnableWindow(FALSE);

	CString str1;
	m_edIp.GetWindowText(str1);
	string ip = GB2312Str::FromUTF16(str1.GetString());

	theApp.GetSrv1().GetMainTcpClient().SetConnectInfo(ip, port);
	theApp.GetSrv1().GetMainTcpClient().Connect();
}


void CClient1Dlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	m_btnConnect.EnableWindow(TRUE);
	m_edIp.EnableWindow(TRUE);
	m_edPort.EnableWindow(TRUE);

	theApp.GetSrv1().GetMainTcpClient().Close();
	ShowLog(_T("user close the connection"));
}
