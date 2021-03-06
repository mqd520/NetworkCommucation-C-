
// NetworkStreamWriteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NetworkStreamWrite.h"
#include "NetworkStreamWriteDlg.h"
#include "afxdialogex.h"
#include "tc/NetworkStreamWrite.h"

using namespace tc;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetworkStreamWriteDlg 对话框

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


CNetworkStreamWriteDlg::CNetworkStreamWriteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetworkStreamWriteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetworkStreamWriteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNetworkStreamWriteDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CNetworkStreamWriteDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CNetworkStreamWriteDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CNetworkStreamWriteDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CNetworkStreamWriteDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CNetworkStreamWriteDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CNetworkStreamWriteDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CNetworkStreamWriteDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CNetworkStreamWriteDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CNetworkStreamWriteDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CNetworkStreamWriteDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CNetworkStreamWriteDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CNetworkStreamWriteDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CNetworkStreamWriteDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CNetworkStreamWriteDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CNetworkStreamWriteDlg::OnBnClickedButton15)
END_MESSAGE_MAP()


// CNetworkStreamWriteDlg 消息处理程序

BOOL CNetworkStreamWriteDlg::OnInitDialog()
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

void CNetworkStreamWriteDlg::OnPaint()
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
HCURSOR CNetworkStreamWriteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetworkStreamWriteDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	BYTE buf2[] = { 1, 2, 3, 4, 5 };
	ns1.WriteBuf(buf2, sizeof(buf2) / sizeof(BYTE));
	PrintfBuf(buf1, ns1.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	BYTE b = 1;
	ns1.WriteByte(b);
	PrintfBuf(buf1, ns1.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteShort(1);
	ns1.WriteShort(-1);
	PrintfBuf(buf1, ns1.WritedCount());


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteShort(1);
	ns2.WriteShort(-1);
	PrintfBuf(buf2, ns2.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteUShort(1);
	PrintfBuf(buf1, ns1.WritedCount());

	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteUShort(1);
	PrintfBuf(buf2, ns2.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteInt16(1);
	ns1.WriteInt16(-2);
	PrintfBuf(buf1, ns1.WritedCount());


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteInt16(1);
	ns2.WriteInt16(-2);
	PrintfBuf(buf2, ns2.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteUInt16(1);
	PrintfBuf(buf1, ns1.WritedCount());


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns1.WriteUInt16(1);
	PrintfBuf(buf1, ns1.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteInt32(1);
	ns1.WriteInt32(-2);
	PrintfBuf(buf1, ns1.WritedCount());


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteInt32(1);
	ns2.WriteInt32(-2);
	PrintfBuf(buf2, ns2.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton8()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteUInt32(1);
	PrintfBuf(buf1, ns1.WritedCount());


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteUInt32(1);
	PrintfBuf(buf2, ns2.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton9()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteInt64(1);
	ns1.WriteInt64(-2);
	PrintfBuf(buf1, ns1.WritedCount());


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteInt64(1);
	ns2.WriteInt64(-2);
	PrintfBuf(buf2, ns2.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton10()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteUInt64(1);
	PrintfBuf(buf1, ns1.WritedCount());


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteUInt64(1);
	PrintfBuf(buf2, ns2.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton11()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteFloat(1);
	ns1.WriteFloat(-2);
	PrintfBuf(buf1, ns1.WritedCount());


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteFloat(1);
	ns2.WriteFloat(-2);
	PrintfBuf(buf2, ns2.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton12()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteDouble(1.11);
	ns1.WriteDouble(-2.22);
	PrintfBuf(buf1, ns1.WritedCount());


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteDouble(1.11);
	ns2.WriteDouble(-2.22);
	PrintfBuf(buf2, ns2.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton13()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteGB2312Str("汉字ABC123");
	PrintfBuf(buf1, ns1.WritedCount());


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteGB2312Str("汉字ABC123", 1, true);
	PrintfBuf(buf2, ns2.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton14()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteUTF16Str(L"汉字ABC123", 4, true);
	PrintfBuf(buf1, ns1.WritedCount());


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteUTF16Str(L"汉字ABC123", 0);
	PrintfBuf(buf2, ns2.WritedCount());
}


void CNetworkStreamWriteDlg::OnBnClickedButton15()
{
	// TODO:  在此添加控件通知处理程序代码

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteUTF8Str("汉字ABC123", 4, true);
	PrintfBuf(buf1, ns1.WritedCount());


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteUTF8Str("汉字ABC123", 2, true);
	PrintfBuf(buf2, ns2.WritedCount());


	BYTE buf3[128] = { 0 };
	CNetworkStreamWrite ns3(buf3, 128, EByteOrder::big);
	ns3.WriteUTF8Str("汉字ABC123", 4);
	PrintfBuf(buf3, ns3.WritedCount());


	BYTE buf4[128] = { 0 };
	CNetworkStreamWrite ns4(buf4, 128, EByteOrder::big);
	ns4.WriteUTF8Str("汉字ABC123", 0);
	PrintfBuf(buf4, ns4.WritedCount());

	BYTE buf5[128] = { 0 };
	CNetworkStreamWrite ns5(buf5, 128, EByteOrder::litte);
	ns5.WriteUTF8Str("汉字ABC123", 0, true);
	PrintfBuf(buf5, ns5.WritedCount());
}
