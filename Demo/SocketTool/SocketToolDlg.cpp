
// SocketToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SocketTool.h"
#include "SocketToolDlg.h"
#include "afxdialogex.h"

#include "tc/SocketTool.h"

using namespace tc;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSocketToolDlg 对话框

void OnSocketErrorCallback(string err, void* lpParam);

CSocketToolDlg::CSocketToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocketToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSocketToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSocketToolDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSocketToolDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSocketToolDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSocketToolDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CSocketToolDlg 消息处理程序

BOOL CSocketToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	SocketTool::RegErrorCallback(OnSocketErrorCallback, this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSocketToolDlg::OnPaint()
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
HCURSOR CSocketToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketToolDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码

	bool b1 = SocketTool::Bind(0, SocketTool::GetLocalIP(), 0);
	bool b2 = SocketTool::Listen(0, SocketTool::GetLocalIP(), 0);
	SOCKET socket = SocketTool::Accept(0, SocketTool::GetLocalIP(), 0);
}

void OnSocketErrorCallback(string err, void* lpParam)
{
	OutputDebugStringA(err.c_str());
	OutputDebugStringA("\n");
}


void CSocketToolDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码

	bool b2 = SocketTool::Bind(0, "192.168.0.69", 0, false);
}


void CSocketToolDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码

	SocketTool::RemoveErrorCallback(OnSocketErrorCallback);
	bool b2 = SocketTool::Bind(0, "192.168.0.69", 0);
}


void CSocketToolDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码

	string ip = SocketTool::GetLocalIP();
	OutputDebugStringA(ip.c_str());
	OutputDebugStringA("\n");
}
