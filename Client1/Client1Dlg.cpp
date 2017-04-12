
// Client1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client1.h"
#include "Client1Dlg.h"
#include "afxdialogex.h"
#include "NetTool.h"
#include "StringHandle.h"

using namespace NetworkCommunication;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CClient1Dlg 对话框



CClient1Dlg::CClient1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClient1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CClient1Dlg::~CClient1Dlg()
{

}

void CClient1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
	DDX_Text(pDX, IDC_EDIT1, m_str1);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipServerIP);
	DDX_Control(pDX, IDC_EDIT2, m_edServerPort);
	DDX_Text(pDX, IDC_IPADDRESS1, m_strServerIP);
	DDX_Text(pDX, IDC_EDIT2, m_nServerPort);
	DDX_Control(pDX, IDC_EDIT3, m_editResult);
	DDX_Text(pDX, IDC_EDIT3, m_strResult);
}

BEGIN_MESSAGE_MAP(CClient1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClient1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClient1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CClient1Dlg::OnBnClickedButton3)
	ON_MESSAGE(WM_CUSTOM_MESSAGE1, &CClient1Dlg::OnRecvData)
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
	//TCHAR ip[20] = { '\0' };
	//if (GetLocalIP(ip))
	//{
	//	m_ipServerIP.SetWindowText(ip);
	//}
	//m_edServerPort.SetWindowText(_T("8080"));

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

void CClient1Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

void CClient1Dlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	BYTE buf[3] = { 48, 49, 50 };
	theApp.m_tcp.SendData(buf, 3);

	theApp.m_tcp.SendData(NULL, 0);
}

void CClient1Dlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
}

LRESULT CClient1Dlg::OnRecvData(WPARAM wparam, LPARAM lparam)
{
	string str = ReadMultiByteStr((BYTE*)wparam, (int)lparam);
	wstring wstr = MultiByteToUTF8(str.c_str());
	m_editResult.SetWindowText(wstr.c_str());
	return 0;
}