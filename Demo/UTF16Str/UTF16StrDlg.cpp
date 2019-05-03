
// UTF16StrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UTF16Str.h"
#include "UTF16StrDlg.h"
#include "afxdialogex.h"
#include "tc/UTF16Str.h"

using namespace tc;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUTF16StrDlg �Ի���



CUTF16StrDlg::CUTF16StrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUTF16StrDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUTF16StrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUTF16StrDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUTF16StrDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUTF16StrDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CUTF16StrDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUTF16StrDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CUTF16StrDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CUTF16StrDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CUTF16StrDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CUTF16StrDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CUTF16StrDlg ��Ϣ�������

BOOL CUTF16StrDlg::OnInitDialog()
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

void CUTF16StrDlg::OnPaint()
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
HCURSOR CUTF16StrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUTF16StrDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf1[] = { 73, 108, 87, 91, 65, 0, 66, 0, 67, 0, 49, 0, 50, 0, 51, 0 };	// ����ABC123, UTF16����(С��)
	wstring strUTF16_1 = UTF16Str::FromBuf(buf1, 16, EByteOrder::litte);
	TRACE(L"%s \n", strUTF16_1.c_str());

	BYTE buf2[] = { 108, 73, 91, 87, 0, 65, 0, 66, 0, 67, 0, 49, 0, 50, 0, 51 };	// ����ABC123, UTF16����(���)
	wstring strUTF16_2 = UTF16Str::FromBuf(buf2, 16, EByteOrder::big);
	TRACE(L"%s \n", strUTF16_2.c_str());
}


void CUTF16StrDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf1[] = { -26, -79, -119, -27, -83, -105, 65, 66, 67, 49, 50, 51 };		// ����ABC123, UTF8����
	wstring strUTF16 = UTF16Str::FromUTF8Buf(buf1, sizeof(buf1) / sizeof(BYTE));
	TRACE(L"%s", strUTF16.c_str());
}


void CUTF16StrDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf[30] = { 0 };
	wstring str = L"����ABC123";
	int len = UTF16Str::ToUTF8Buf(str, buf);
	for (int i = 0; i < len; i++)
	{
		char ch[10] = { 0 };
		sprintf_s(ch, "%d, ", buf[i]);
		OutputDebugStringA(ch);
	}
	TRACE("\n");
}


void CUTF16StrDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	string strGB2312 = "����ABC123";
	wstring strUTF16 = UTF16Str::FromGB2312(strGB2312);
	TRACE(L"%s \n", strUTF16.c_str());
}


void CUTF16StrDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	int n = UTF16Str::GetByteCount(L"����ABC123");
	TRACE("%d \n", n);
}


void CUTF16StrDlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf1[32] = { 0 };
	int n1 = UTF16Str::ToBuf(L"����ABC123", buf1, EByteOrder::big);
	for (int i = 0; i < n1; i++)
	{
		char ch[10] = { 0 };
		sprintf_s(ch, "%d, ", buf1[i]);
		OutputDebugStringA(ch);
	}
	TRACE("\n");

	BYTE buf2[32] = { 0 };
	int n2 = UTF16Str::ToBuf(L"����ABC123", buf2, EByteOrder::litte);
	for (int i = 0; i < n2; i++)
	{
		char ch[10] = { 0 };
		sprintf_s(ch, "%d, ", buf2[i]);
		OutputDebugStringA(ch);
	}
	TRACE("\n");
}


void CUTF16StrDlg::OnBnClickedButton7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf1[] = { -26, -79, -119, -27, -83, -105, 65, 66, 67, 49, 50, 51 };		// ����ABC123, UTF8����
	BYTE buf2[30] = { 0 };
	int len2 = 0;
	UTF16Str::UTF8_2_UTF16(buf1, sizeof(buf1) / sizeof(BYTE), buf2, &len2, EByteOrder::litte);
	for (int i = 0; i < len2; i++)
	{
		char ch[20] = { 0 };
		sprintf_s(ch, "%d, ", buf2[i]);
		OutputDebugStringA(ch);
	}
	TRACE("\n");


	BYTE buf3[] = { -26, -79, -119, -27, -83, -105, 65, 66, 67, 49, 50, 51 };		// ����ABC123, UTF8����
	BYTE buf4[30] = { 0 };
	int len4 = 0;
	UTF16Str::UTF8_2_UTF16(buf3, sizeof(buf3) / sizeof(BYTE), buf4, &len4, EByteOrder::big);
	for (int i = 0; i < len4; i++)
	{
		char ch[20] = { 0 };
		sprintf_s(ch, "%d, ", buf4[i]);
		OutputDebugStringA(ch);
	}
	TRACE("\n");
}


void CUTF16StrDlg::OnBnClickedButton8()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf1[] = { 73, 108, 87, 91, 65, 0, 66, 0, 67, 0, 49, 0, 50, 0, 51, 0 };		// ����ABC123, UTF16����(С��)
	BYTE buf2[30] = { 0 };
	int len2 = 0;
	UTF16Str::UTF16_2_UTF8(buf1, sizeof(buf1) / sizeof(BYTE), buf2, &len2, EByteOrder::litte);
	for (int i = 0; i < len2; i++)
	{
		char ch[20] = { 0 };
		sprintf_s(ch, "%d, ", buf2[i]);
		OutputDebugStringA(ch);
	}
	TRACE("\n");


	BYTE buf3[] = { 108, 73, 91, 87, 0, 65, 0, 66, 0, 67, 0, 49, 0, 50, 0, 51 };	// ����ABC123, UTF16����(���)
	BYTE buf4[30] = { 0 };
	int len4 = 0;
	UTF16Str::UTF16_2_UTF8(buf3, sizeof(buf3) / sizeof(BYTE), buf4, &len4, EByteOrder::big);
	for (int i = 0; i < len4; i++)
	{
		char ch[20] = { 0 };
		sprintf_s(ch, "%d, ", buf4[i]);
		OutputDebugStringA(ch);
	}
	TRACE("\n");
}
