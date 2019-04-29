
// NetworkStreamReadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NetworkStreamRead.h"
#include "NetworkStreamReadDlg.h"
#include "afxdialogex.h"
#include "nc/NetworkStreamRead.h"

using namespace NetworkCommunication;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetworkStreamReadDlg 对话框



CNetworkStreamReadDlg::CNetworkStreamReadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetworkStreamReadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetworkStreamReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNetworkStreamReadDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNetworkStreamReadDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNetworkStreamReadDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDCANCEL2, &CNetworkStreamReadDlg::OnBnClickedCancel2)
	ON_BN_CLICKED(IDCANCEL3, &CNetworkStreamReadDlg::OnBnClickedCancel3)
	ON_BN_CLICKED(IDCANCEL4, &CNetworkStreamReadDlg::OnBnClickedCancel4)
	ON_BN_CLICKED(IDCANCEL5, &CNetworkStreamReadDlg::OnBnClickedCancel5)
	ON_BN_CLICKED(IDCANCEL6, &CNetworkStreamReadDlg::OnBnClickedCancel6)
	ON_BN_CLICKED(IDCANCEL7, &CNetworkStreamReadDlg::OnBnClickedCancel7)
	ON_BN_CLICKED(IDCANCEL8, &CNetworkStreamReadDlg::OnBnClickedCancel8)
	ON_BN_CLICKED(IDCANCEL9, &CNetworkStreamReadDlg::OnBnClickedCancel9)
	ON_BN_CLICKED(IDCANCEL10, &CNetworkStreamReadDlg::OnBnClickedCancel10)
	ON_BN_CLICKED(IDCANCEL11, &CNetworkStreamReadDlg::OnBnClickedCancel11)
	ON_BN_CLICKED(IDCANCEL12, &CNetworkStreamReadDlg::OnBnClickedCancel12)
	ON_BN_CLICKED(IDCANCEL13, &CNetworkStreamReadDlg::OnBnClickedCancel13)
	ON_BN_CLICKED(IDOK2, &CNetworkStreamReadDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CNetworkStreamReadDlg 消息处理程序

BOOL CNetworkStreamReadDlg::OnInitDialog()
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

void CNetworkStreamReadDlg::OnPaint()
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
HCURSOR CNetworkStreamReadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetworkStreamReadDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf[5] = { 1, 2, 3, 4, 5 };

	CNetworkStreamRead ns(buf, 5, EByteOrder::big);
	BYTE b1 = ns.ReadByte();
	BYTE b2 = ns.ReadByte();
	BYTE b3 = ns.ReadByte();

	TRACE("b1 = %d, b2 = %d, b3 = %d \n", b1, b2, b3);
}


void CNetworkStreamReadDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf1[2] = { 1, 2 };
	CNetworkStreamRead ns1(buf1, 2, EByteOrder::litte);
	short s1 = ns1.ReadShort();
	TRACE("s1(litte) = %d \n", s1);

	BYTE buf2[2] = { 1, 2 };
	CNetworkStreamRead ns2(buf2, 2, EByteOrder::big);
	short s2 = ns2.ReadShort();
	TRACE("s2(big) = %d \n", s2);

	BYTE buf3[2] = { 1, 130 };	// 负数
	CNetworkStreamRead ns3(buf3, 2, EByteOrder::litte);
	short s3 = ns3.ReadShort();
	TRACE("-s3(litte) = %d \n", s3);

	BYTE buf4[2] = { 129, 2 };	// 负数
	CNetworkStreamRead ns4(buf4, 2, EByteOrder::big);
	short s4 = ns4.ReadShort();
	TRACE("-s4(big) = %d \n", s4);
}


void CNetworkStreamReadDlg::OnBnClickedCancel2()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf1[2] = { 1, 2 };
	CNetworkStreamRead ns1(buf1, 2, EByteOrder::litte);
	USHORT s1 = ns1.ReadUShort();
	TRACE("s1(litte) = %d \n", s1);

	BYTE buf2[2] = { 1, 2 };
	CNetworkStreamRead ns2(buf2, 2, EByteOrder::big);
	USHORT s2 = ns2.ReadUShort();
	TRACE("s2(big) = %d \n", s2);

	BYTE buf3[2] = { 1, 130 };	// 负数
	CNetworkStreamRead ns3(buf3, 2, EByteOrder::litte);
	USHORT s3 = ns3.ReadUShort();
	TRACE("-s3(litte) = %d \n", s3);

	BYTE buf4[2] = { 129, 2 };	// 负数
	CNetworkStreamRead ns4(buf4, 2, EByteOrder::big);
	USHORT s4 = ns4.ReadUShort();
	TRACE("-s4(big) = %d \n", s4);
}


void CNetworkStreamReadDlg::OnBnClickedCancel3()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CNetworkStreamReadDlg::OnBnClickedCancel4()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CNetworkStreamReadDlg::OnBnClickedCancel5()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf1[4] = { 1, 2, 3, 4 };
	CNetworkStreamRead ns1(buf1, 4, EByteOrder::litte);
	INT32 s1 = ns1.ReadInt32();
	TRACE("s1(litte) = %d \n", s1);

	BYTE buf2[4] = { 1, 2, 3, 4 };
	CNetworkStreamRead ns2(buf2, 4, EByteOrder::big);
	INT32 s2 = ns2.ReadInt32();
	TRACE("s2(big) = %d \n", s2);

	BYTE buf3[4] = { 1, 2, 3, -4 };	// 负数
	CNetworkStreamRead ns3(buf3, 4, EByteOrder::litte);
	INT32 s3 = ns3.ReadInt32();
	TRACE("-s3(litte) = %d \n", s3);

	BYTE buf4[4] = { -1, 2, 3, 4 };	// 负数
	CNetworkStreamRead ns4(buf4, 4, EByteOrder::big);
	INT32 s4 = ns4.ReadInt32();
	TRACE("-s4(big) = %d \n", s4);
}


void CNetworkStreamReadDlg::OnBnClickedCancel6()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CNetworkStreamReadDlg::OnBnClickedCancel7()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CNetworkStreamReadDlg::OnBnClickedCancel8()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CNetworkStreamReadDlg::OnBnClickedCancel9()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CNetworkStreamReadDlg::OnBnClickedCancel10()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CNetworkStreamReadDlg::OnBnClickedCancel11()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf1[] = { 0xBA, 0xBA, 0xD7, 0xD6, 65, 66, 67, 49, 50, 51 };
	CNetworkStreamRead ns1(buf1, 10, EByteOrder::litte);
	char ch1[20] = { 0 };
	ns1.ReadGB2312Str(ch1, 10);
	TRACE("%s \n", ch1);

	BYTE buf2[] = { 0, 0, 0, 10, 0xBA, 0xBA, 0xD7, 0xD6, 65, 66, 67, 49, 50, 51 };
	CNetworkStreamRead ns2(buf2, 14, EByteOrder::big);
	char ch2[20] = { 0 };
	ns2.ReadGB2312Str(ch2);
	TRACE("%s \n", ch2);

	BYTE buf3[] = { 10, 0, 0, 0, 0xBA, 0xBA, 0xD7, 0xD6, 65, 66, 67, 49, 50, 51 };
	CNetworkStreamRead ns3(buf3, 14, EByteOrder::litte);
	char ch3[20] = { 0 };
	ns3.ReadGB2312Str(ch3);
	TRACE("%s \n", ch3);
}


void CNetworkStreamReadDlg::OnBnClickedCancel12()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf1[] = { 0x6C, 0x49, 0x5B, 0x57, 0, 65, 0, 66, 0, 67, 0, 49, 0, 50, 0, 51 };
	CNetworkStreamRead ns1(buf1, 16, EByteOrder::big);
	wchar_t ch1[20] = { 0 };
	ns1.ReadUTF16Str(ch1, 16);
	TRACE(L"%s \n", ch1);

	BYTE buf2[] = { 0x49, 0x6C, 0x57, 0x5B, 65, 0, 66, 0, 67, 0, 49, 0, 50, 0, 51, 0 };
	CNetworkStreamRead ns2(buf2, 16, EByteOrder::litte);
	wchar_t ch2[20] = { 0 };
	ns2.ReadUTF16Str(ch2, 16);
	TRACE(L"%s \n", ch2);

	BYTE buf3[] = { 16, 0, 0, 0, 0x49, 0x6C, 0x57, 0x5B, 65, 0, 66, 0, 67, 0, 49, 0, 50, 0, 51, 0 };
	CNetworkStreamRead ns3(buf3, 20, EByteOrder::litte);
	wchar_t ch3[20] = { 0 };
	ns3.ReadUTF16Str(ch3);
	TRACE(L"%s \n", ch3);
}


void CNetworkStreamReadDlg::OnBnClickedCancel13()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf1[] = { -26, -79, -119 };
	CNetworkStreamRead ns1(buf1, 3, EByteOrder::big);
	wchar_t ch1[20] = { 0 };
	ns1.ReadUTF8Str(ch1, 16);
	TRACE(L"%s \n", ch1);
}


void CNetworkStreamReadDlg::OnBnClickedOk2()
{
	// TODO:  在此添加控件通知处理程序代码
}
