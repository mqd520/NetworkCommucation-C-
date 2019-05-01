
// GB2312StrDlg.cpp : ʵ���ļ�
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


// CGB2312StrDlg �Ի���



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


// CGB2312StrDlg ��Ϣ�������

BOOL CGB2312StrDlg::OnInitDialog()
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

void CGB2312StrDlg::OnPaint()
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
HCURSOR CGB2312StrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGB2312StrDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf1[] = { 0xBA, 0xBA, 0xD7, 0xD6, 65, 66, 67, 49, 50, 51 };	// ����ABC123, GB2312����
	string strGB2312 = GB2312Str::FromBuf(buf1, 10);
	TRACE("%s \n", strGB2312.c_str());
}


void CGB2312StrDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	wstring strUTF16 = L"����ABC123";
	string strGB2312 = GB2312Str::FromUTF16(strUTF16);
	TRACE("%s \n", strGB2312.c_str());
}


void CGB2312StrDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf1[] = { -26, -79, -119, -27, -83, -105, 65, 66, 67, 49, 50, 51 };	// ����ABC123, UTF8����
	string strGB2312 = GB2312Str::FromUTF8Buf(buf1, sizeof(buf1) / sizeof(BYTE));
	TRACE("%s \n", strGB2312.c_str());
}


void CGB2312StrDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf[100] = { 0 };
	int n = GB2312Str::ToUTF8Buf("����ABC123", buf);
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	int n = GB2312Str::GetByteCount("����ABC123");
	TRACE("%d \n", n);
}


void CGB2312StrDlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	string strGB2312 = "����ABC123";
	BYTE buf[1024] = { 0 };
	int n = GB2312Str::ToBuf(strGB2312, buf);
	TRACE("%d \n", n);
}
