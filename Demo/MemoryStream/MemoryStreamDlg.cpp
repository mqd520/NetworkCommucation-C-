
// MemoryStreamDlg.cpp : ʵ���ļ�
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


// CMemoryStreamDlg �Ի���

int _maxSize = 22;
MemoryStream _ms(_maxSize);	// �ڴ�������

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


// CMemoryStreamDlg ��Ϣ�������

BOOL CMemoryStreamDlg::OnInitDialog()
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

void CMemoryStreamDlg::OnPaint()
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
HCURSOR CMemoryStreamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMemoryStreamDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	int n = _ms.GetTotalLen();
	Print1(n);
}


void CMemoryStreamDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	int n = _ms.AvaliableReadLen();
	Print1(n);
}


void CMemoryStreamDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	int n = _ms.AvaliableWriteLen();
	Print1(n);
}


void CMemoryStreamDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf[2] = { 0 };
	_ms.Copy(buf, sizeof(buf) / sizeof(BYTE));
	PrintfBuf(buf, sizeof(buf) / sizeof(BYTE));

	PrintfBuf(_ms.GetBuf(), _ms.GetTotalLen());
}


void CMemoryStreamDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf[3] = { 0 };
	_ms.Read(buf, sizeof(buf) / sizeof(BYTE));
	PrintfBuf(buf, sizeof(buf) / sizeof(BYTE));

	PrintfBuf(_ms.GetBuf(), _ms.GetTotalLen());
}


void CMemoryStreamDlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	_ms.Write(buf, sizeof(buf) / sizeof(BYTE));

	PrintfBuf(_ms.GetBuf(), _ms.GetTotalLen());
}


void CMemoryStreamDlg::OnBnClickedButton7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	_ms.Clear();
	PrintfBuf(_ms.GetBuf(), _ms.GetTotalLen());
}
