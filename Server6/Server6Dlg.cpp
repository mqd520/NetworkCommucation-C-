
// Server6Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Server6.h"
#include "Server6Dlg.h"
#include "afxdialogex.h"
#include "MemoryTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServer6Dlg 对话框



CServer6Dlg::CServer6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServer6Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServer6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipServerIP);
	DDX_Control(pDX, IDC_EDIT1, m_edServerPort);
	DDX_Control(pDX, IDC_BUTTON1, m_btnListen);
	DDX_Control(pDX, IDC_LIST1, m_lcClientData);
}

BEGIN_MESSAGE_MAP(CServer6Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CServer6Dlg::OnBnClickedButton1)
	ON_MESSAGE(WM_RECVNEWCONNECTION, &CServer6Dlg::OnRecvNewConnection)
END_MESSAGE_MAP()


// CServer6Dlg 消息处理程序

BOOL CServer6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_ipServerIP.SetWindowTextW(L"192.168.0.68");
	m_edServerPort.SetWindowTextW(L"8040");
	m_lcClientData.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 40, -1);
	m_lcClientData.InsertColumn(1, _T("客户端IP"), LVCFMT_CENTER, 120, -1);
	m_lcClientData.InsertColumn(2, _T("客户端端口"), LVCFMT_CENTER, 80, -1);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServer6Dlg::OnPaint()
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
HCURSOR CServer6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServer6Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strServerIP, strServerPort;
	m_ipServerIP.GetWindowTextW(strServerIP);
	m_edServerPort.GetWindowTextW(strServerPort);
	int nServerPort = _wtoi(strServerPort.GetBuffer());

	if (nServerPort > 0)
	{
		theApp.m_tcpSrv.Listen(strServerIP.GetBuffer(), nServerPort);

		m_btnListen.EnableWindow(FALSE);
		m_edServerPort.EnableWindow(FALSE);
		m_ipServerIP.EnableWindow(FALSE);
	}
	else
	{
		MessageBoxW(L"请输入正确的IP和端口", L"Title");
	}
}

LRESULT CServer6Dlg::OnRecvNewConnection(WPARAM wParam, LPARAM lParam)
{
	int index = (int)wParam;
	TcpSessionData session = theApp.m_sessionMgr.GetDataByIndex(index);
	CString strNumber, strPort;
	strNumber.Format(_T("%d"), index + 1);
	strPort.Format(_T("%d"), session.port);

	m_lcClientData.InsertItem(LVIF_TEXT | LVIF_STATE, index, strNumber.GetBuffer(), 0, 0, 0, 0);
	m_lcClientData.SetItemText(index, 1, session.ip);
	m_lcClientData.SetItemText(index, 2, strPort.GetBuffer());

	return 1;
}
