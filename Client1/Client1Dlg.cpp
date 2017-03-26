
// Client1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client1.h"
#include "Client1Dlg.h"
#include "afxdialogex.h"
#include "TcpClient.h"
#include "Common.h"

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
	if (m_tcpClient)
	{
		delete m_tcpClient;
	}
}

void CClient1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST4, m_lc1);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
}

BEGIN_MESSAGE_MAP(CClient1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(TCPClientRecvMsg, OnTCPClientRecvMsg)
	ON_BN_CLICKED(IDC_BUTTON1, &CClient1Dlg::OnBnClickedButton1)
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
	m_tcpClient = new CTcpClient(this->m_hWnd, _T("192.168.0.15"), 8011);
	m_lc1.InsertColumn(0, _T("Col1"), 0, 100);

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
	if (m_tcpClient->StartConnect())
	{
		//MessageBox(_T("连接成功!"));
		m_btn1.EnableWindow(false);
	}
	else
	{
		//MessageBox(_T("连接失败!"));
	}
}

afx_msg LRESULT CClient1Dlg::OnTCPClientRecvMsg(WPARAM wParam, LPARAM lParam)
{
	char* str1 = (char*)wParam;
	char ch[3] = { '\0' };
	strncpy(ch, str1, 2);
	wchar_t* str = MultiByteToUTF8(ch);
	MessageBox(str);
	//int i = m_lc1.GetItemCount();
	//m_lc1.InsertItem(i, str);
	//delete str;
	return 0;
}
