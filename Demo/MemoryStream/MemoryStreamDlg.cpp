
// MemoryStreamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemoryStream.h"
#include "MemoryStreamDlg.h"
#include "afxdialogex.h"
#include "tc/MemoryStream.h"

using namespace tc;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMemoryStreamDlg 对话框

int _maxSize = 22;
MemoryStream _ms(_maxSize);	// 内存流对象

void PrintfBuf(BYTE* pBuf, int len)
{
	for (int i = 0; i < len; i++)
	{
		char ch[10] = { 0 };
		sprintf_s(ch, "%d, ", pBuf[i]);
		OutputDebugStringA(ch);
	}
	OutputDebugStringA("\n");
}

void Print1(int n)
{
	char ch[100] = { 0 };
	sprintf_s(ch, "%d", n);
	OutputDebugStringA(ch);
	OutputDebugStringA("\n");
}


CMemoryStreamDlg::CMemoryStreamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMemoryStreamDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMemoryStreamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMemoryStreamDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMemoryStreamDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMemoryStreamDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMemoryStreamDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMemoryStreamDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMemoryStreamDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMemoryStreamDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMemoryStreamDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CMemoryStreamDlg 消息处理程序

BOOL CMemoryStreamDlg::OnInitDialog()
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

void CMemoryStreamDlg::OnPaint()
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
HCURSOR CMemoryStreamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMemoryStreamDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码

	int n = _ms.GetTotalLen();
	Print1(n);
}


void CMemoryStreamDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码

	int n = _ms.AvaliableReadLen();
	Print1(n);
}


void CMemoryStreamDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码

	int n = _ms.AvaliableWriteLen();
	Print1(n);
}


void CMemoryStreamDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf[2] = { 0 };
	_ms.Copy(buf, sizeof(buf) / sizeof(BYTE));
	PrintfBuf(buf, sizeof(buf) / sizeof(BYTE));

	PrintfBuf(_ms.GetBuf(), _ms.GetTotalLen());
}


void CMemoryStreamDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf[3] = { 0 };
	_ms.Read(buf, sizeof(buf) / sizeof(BYTE));
	PrintfBuf(buf, sizeof(buf) / sizeof(BYTE));

	PrintfBuf(_ms.GetBuf(), _ms.GetTotalLen());
}


void CMemoryStreamDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	_ms.Write(buf, sizeof(buf) / sizeof(BYTE));

	PrintfBuf(_ms.GetBuf(), _ms.GetTotalLen());
}


void CMemoryStreamDlg::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码

	_ms.Clear();
	PrintfBuf(_ms.GetBuf(), _ms.GetTotalLen());
}
