
// Tool1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tool1.h"
#include "Tool1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTool1Dlg 对话框

void OnTimer1(Timer* pTimer, int count, void* pParam1, void* pParam2);

CTool1Dlg::CTool1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTool1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTool1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTool1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTool1Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTool1Dlg 消息处理程序

BOOL CTool1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	timer1.SetCallback(OnTimer1, this);
	timer1.SetTimeout(1 * 1000);

	timer2.SetCallback(OnTimer1, this);
	timer2.SetTimeout(3 * 1000);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTool1Dlg::OnPaint()
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
HCURSOR CTool1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTool1Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	timer1.Run();
	timer2.Run();
}

void OnTimer1(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
{
	SYSTEMTIME time;
	GetSystemTime(&time);

	wchar_t ch[1024] = { 0 };
	swprintf_s(ch, L"OnTimer1: count = %02d, time = %02d:%02d:%02d:%03d \n", count, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	OutputDebugString(ch);
}