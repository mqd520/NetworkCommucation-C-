
// NetworkStreamReadDlg.cpp : ʵ���ļ�
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


// CNetworkStreamReadDlg �Ի���



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


// CNetworkStreamReadDlg ��Ϣ�������

BOOL CNetworkStreamReadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNetworkStreamReadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CNetworkStreamReadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetworkStreamReadDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf[5] = { 1, 2, 3, 4, 5 };

	CNetworkStreamRead ns(buf, 5, EByteOrder::big);
	BYTE b1 = ns.ReadByte();
	BYTE b2 = ns.ReadByte();
	BYTE b3 = ns.ReadByte();

	TRACE("b1 = %d, b2 = %d, b3 = %d \n", b1, b2, b3);
}


void CNetworkStreamReadDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	BYTE buf1[2] = { 1, 2 };
	CNetworkStreamRead ns1(buf1, 2, EByteOrder::litte);
	short s1 = ns1.ReadShort();
	TRACE("s1(litte) = %d \n", s1);

	BYTE buf2[2] = { 1, 2 };
	CNetworkStreamRead ns2(buf2, 2, EByteOrder::big);
	short s2 = ns2.ReadShort();
	TRACE("s2(big) = %d \n", s2);

	BYTE buf3[2] = { 1, 130 };	// ����
	CNetworkStreamRead ns3(buf3, 2, EByteOrder::litte);
	short s3 = ns3.ReadShort();
	TRACE("-s3(litte) = %d \n", s3);

	BYTE buf4[2] = { 129, 2 };	// ����
	CNetworkStreamRead ns4(buf4, 2, EByteOrder::big);
	short s4 = ns4.ReadShort();
	TRACE("-s4(big) = %d \n", s4);
}


void CNetworkStreamReadDlg::OnBnClickedCancel2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	BYTE buf1[2] = { 1, 2 };
	CNetworkStreamRead ns1(buf1, 2, EByteOrder::litte);
	USHORT s1 = ns1.ReadUShort();
	TRACE("s1(litte) = %d \n", s1);

	BYTE buf2[2] = { 1, 2 };
	CNetworkStreamRead ns2(buf2, 2, EByteOrder::big);
	USHORT s2 = ns2.ReadUShort();
	TRACE("s2(big) = %d \n", s2);

	BYTE buf3[2] = { 1, 130 };	// ����
	CNetworkStreamRead ns3(buf3, 2, EByteOrder::litte);
	USHORT s3 = ns3.ReadUShort();
	TRACE("-s3(litte) = %d \n", s3);

	BYTE buf4[2] = { 129, 2 };	// ����
	CNetworkStreamRead ns4(buf4, 2, EByteOrder::big);
	USHORT s4 = ns4.ReadUShort();
	TRACE("-s4(big) = %d \n", s4);
}


void CNetworkStreamReadDlg::OnBnClickedCancel3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CNetworkStreamReadDlg::OnBnClickedCancel4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CNetworkStreamReadDlg::OnBnClickedCancel5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	BYTE buf1[4] = { 1, 2, 3, 4 };
	CNetworkStreamRead ns1(buf1, 4, EByteOrder::litte);
	INT32 s1 = ns1.ReadInt32();
	TRACE("s1(litte) = %d \n", s1);

	BYTE buf2[4] = { 1, 2, 3, 4 };
	CNetworkStreamRead ns2(buf2, 4, EByteOrder::big);
	INT32 s2 = ns2.ReadInt32();
	TRACE("s2(big) = %d \n", s2);

	BYTE buf3[4] = { 1, 2, 3, -4 };	// ����
	CNetworkStreamRead ns3(buf3, 4, EByteOrder::litte);
	INT32 s3 = ns3.ReadInt32();
	TRACE("-s3(litte) = %d \n", s3);

	BYTE buf4[4] = { -1, 2, 3, 4 };	// ����
	CNetworkStreamRead ns4(buf4, 4, EByteOrder::big);
	INT32 s4 = ns4.ReadInt32();
	TRACE("-s4(big) = %d \n", s4);
}


void CNetworkStreamReadDlg::OnBnClickedCancel6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CNetworkStreamReadDlg::OnBnClickedCancel7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CNetworkStreamReadDlg::OnBnClickedCancel8()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CNetworkStreamReadDlg::OnBnClickedCancel9()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CNetworkStreamReadDlg::OnBnClickedCancel10()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CNetworkStreamReadDlg::OnBnClickedCancel11()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	BYTE buf1[] = { -26, -79, -119 };
	CNetworkStreamRead ns1(buf1, 3, EByteOrder::big);
	wchar_t ch1[20] = { 0 };
	ns1.ReadUTF8Str(ch1, 16);
	TRACE(L"%s \n", ch1);
}


void CNetworkStreamReadDlg::OnBnClickedOk2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
