
// Client2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client2.h"
#include "Client2Dlg.h"
#include "afxdialogex.h"
#include "Protocol1Handle.h"

using namespace Protocol1;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CClient2Dlg 对话框



CClient2Dlg::CClient2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClient2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClient2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClient2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CClient2Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CClient2Dlg 消息处理程序

BOOL CClient2Dlg::OnInitDialog()
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

void CClient2Dlg::OnPaint()
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
HCURSOR CClient2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClient2Dlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	CProtocol1Handle handler;
	//业务数据
	char* str = "123";
	//业务数据转字节数组
	BYTE* buf1 = (BYTE*)str;
	//封包
	LPPackage1 pack1 = handler.Packet(Package1Type::type1, buf1, 4);
	//发送
	BYTE* buf2 = handler.GetBuffer(pack1);
	//...

	//解包
	int len = 11;
	LPPackage1 pack2 = handler.UnPacket(buf2, len);
	int datalen = handler.GetDataLen(pack2);
	BYTE buf3[1024];
	memcpy(buf3, pack2->data, datalen);

	delete buf2;
	handler.ReleaseMemory(pack2);
	handler.ReleaseMemory(pack1);
}
