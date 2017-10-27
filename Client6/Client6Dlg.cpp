
// Client6Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client6.h"
#include "Client6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClient6Dlg 对话框

void OnTimer(CTimer* pTimer, int count);

CClient6Dlg::CClient6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClient6Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CClient6Dlg::~CClient6Dlg()
{
	if (m_pTimer1)
	{
		delete m_pTimer1;
	}
	if (m_pTimer2)
	{
		delete m_pTimer2;
	}
	if (m_pTimer3)
	{
		delete m_pTimer3;
	}
	if (m_pTimer4)
	{
		delete m_pTimer4;
	}
	if (m_pTimer5)
	{
		delete m_pTimer5;
	}
}

void CClient6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
	DDX_Control(pDX, IDC_BUTTON3, m_btn3);
	DDX_Control(pDX, IDC_BUTTON4, m_btn4);
	DDX_Control(pDX, IDC_BUTTON5, m_btn5);
}

BEGIN_MESSAGE_MAP(CClient6Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClient6Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClient6Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CClient6Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CClient6Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CClient6Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CClient6Dlg 消息处理程序

BOOL CClient6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_pTimer1 = new CTimer(1 * 1000, ::OnTimer);
	m_pTimer1->Run();
	m_pTimer2 = new CTimer(2 * 1000, ::OnTimer);
	m_pTimer2->Run();
	m_pTimer3 = new CTimer(3 * 1000, ::OnTimer);
	m_pTimer3->Run();
	m_pTimer4 = new CTimer(4 * 1000, ::OnTimer);
	m_pTimer4->Run();
	m_pTimer5 = new CTimer(5 * 1000, ::OnTimer);
	m_pTimer5->Run();



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClient6Dlg::OnPaint()
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
HCURSOR CClient6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClient6Dlg::OnCustomTimer(CTimer* pTimer, int count)
{
	if (pTimer == m_pTimer1)
	{
		CString str;
		m_btn1.GetWindowText(str);
		int n = _wtoi(str.GetBuffer());
		n += 1;
		str.Format(L"%d", n);
		m_btn1.SetWindowText(str);
	}
	else if (pTimer == m_pTimer2)
	{
		CString str;
		m_btn2.GetWindowText(str);
		int n = _wtoi(str.GetBuffer());
		n += 2;
		str.Format(L"%d", n);
		m_btn2.SetWindowText(str);
	}
	else if (pTimer == m_pTimer3)
	{
		CString str;
		m_btn3.GetWindowText(str);
		int n = _wtoi(str.GetBuffer());
		n += 3;
		str.Format(L"%d", n);
		m_btn3.SetWindowText(str);
	}
	else if (pTimer == m_pTimer4)
	{
		CString str;
		m_btn4.GetWindowText(str);
		int n = _wtoi(str.GetBuffer());
		n += 4;
		str.Format(L"%d", n);
		m_btn4.SetWindowText(str);
	}
	else if (pTimer == m_pTimer5)
	{
		CString str;
		m_btn5.GetWindowText(str);
		int n = _wtoi(str.GetBuffer());
		n += 5;
		str.Format(L"%d", n);
		m_btn5.SetWindowText(str);
	}
}

void OnTimer(CTimer* pTimer, int count)
{
	((CClient6Dlg*)theApp.m_pMainWnd)->OnCustomTimer(pTimer, count);
}



void CClient6Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_pTimer1->IsRun())
	{
		m_pTimer1->Pause();
	}
	else
	{
		m_pTimer1->Run(true);
	}
}


void CClient6Dlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_pTimer2->IsRun())
	{
		m_pTimer2->Pause();
	}
	else
	{
		m_pTimer2->Run(true);
	}
}


void CClient6Dlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_pTimer3->IsRun())
	{
		m_pTimer3->Pause();
	}
	else
	{
		m_pTimer3->Run(true);
	}
}


void CClient6Dlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_pTimer4->IsRun())
	{
		m_pTimer4->Pause();
	}
	else
	{
		m_pTimer4->Run(true);
	}
}


void CClient6Dlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_pTimer5->IsRun())
	{
		m_pTimer5->Pause();
	}
	else
	{
		m_pTimer5->Run(true);
	}
}
