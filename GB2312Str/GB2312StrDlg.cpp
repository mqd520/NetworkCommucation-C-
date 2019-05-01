
// GB2312StrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GB2312Str.h"
#include "GB2312StrDlg.h"
#include "afxdialogex.h"
#include "nc/GB2312Str.h"

using namespace NetworkCommunication;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGB2312StrDlg 对话框



CGB2312StrDlg::CGB2312StrDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CGB2312StrDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGB2312StrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGB2312StrDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGB2312StrDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGB2312StrDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CGB2312StrDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CGB2312StrDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CGB2312StrDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CGB2312StrDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CGB2312StrDlg 消息处理程序

BOOL CGB2312StrDlg::OnInitDialog()
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

void CGB2312StrDlg::OnPaint()
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
HCURSOR CGB2312StrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGB2312StrDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[] = { 0xBA, 0xBA, 0xD7, 0xD6, 65, 66, 67, 49, 50, 51 };	// 汉字ABC123, GB2312编码
	string strGB2312 = GB2312Str::FromBuf(buf1, 10);
	TRACE("%s \n", strGB2312.c_str());
}


void CGB2312StrDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码

	wstring strUTF16 = L"汉字ABC123";
	string strGB2312 = GB2312Str::FromUTF16(strUTF16);
	TRACE("%s \n", strGB2312.c_str());
}


void CGB2312StrDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[] = { -26, -79, -119, -27, -83, -105, 65, 66, 67, 49, 50, 51 };	// 汉字ABC123, UTF8编码
	string strGB2312 = GB2312Str::FromUTF8Buf(buf1, sizeof(buf1) / sizeof(BYTE));
	TRACE("%s \n", strGB2312.c_str());
}


void CGB2312StrDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf[100] = { 0 };
	int n = GB2312Str::ToUTF8Buf("汉字ABC123", buf);
	for (int i = 0; i < n; i ++)
	{
		char ch[10] = { 0 };
		sprintf_s(ch, "%d, ", buf[i]);
		OutputDebugStringA(ch);
	}
	TRACE("\n");
}


void CGB2312StrDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码

	int n = GB2312Str::GetByteCount("汉字ABC123");
	TRACE("%d \n", n);
}


void CGB2312StrDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码

	string strGB2312 = "汉字ABC123";
	BYTE buf[1024] = { 0 };
	int n = GB2312Str::ToBuf(strGB2312, buf);
	TRACE("%d \n", n);
}
