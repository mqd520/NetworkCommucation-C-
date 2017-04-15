
// Client3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client3.h"
#include "Client3Dlg.h"
#include "afxdialogex.h"
#include "NetTool.h"
#include "StringHandle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClient3Dlg 对话框

CClient3Dlg::CClient3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClient3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClient3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClient3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClient3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClient3Dlg::OnBnClickedButton2)
	ON_MESSAGE(WM_CUSTOM_MESSAGE1, &CClient3Dlg::OnRecvData)
END_MESSAGE_MAP()


// CClient3Dlg 消息处理程序

BOOL CClient3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClient3Dlg::OnPaint()
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
HCURSOR CClient3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClient3Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	DemoPackage1 packet1;
	packet1.strUsername = _T("eguser001");
	packet1.strPwd = _T("123456");
	theApp.m_demoProtocol.SimulateServerData(DemoPackageType::type1, &packet1);
}


void CClient3Dlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	DemoPackage1 packet1;
	packet1.strUsername = _T("eguser001");
	packet1.strPwd = _T("123456");
	theApp.m_demoProtocol.SendData(DemoPackageType::type1, &packet1);
}

LRESULT CClient3Dlg::OnRecvData(WPARAM wparam, LPARAM lparam)
{
	UpdateData(true);
	return 0;
}