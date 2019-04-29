
// StringToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StringTool.h"
#include "StringToolDlg.h"
#include "afxdialogex.h"
#include "nc/StringTool.h"

using namespace NetworkCommunication;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStringToolDlg �Ի���



CStringToolDlg::CStringToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStringToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStringToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStringToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CStringToolDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CStringToolDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CStringToolDlg ��Ϣ�������

BOOL CStringToolDlg::OnInitDialog()
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

void CStringToolDlg::OnPaint()
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
HCURSOR CStringToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStringToolDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	BYTE buf1[] = { -26, -79, -119 };

	BYTE buf2[128] = { 0 };
	int len1 = StringTool::UTF8_UTF16(buf1, 3, buf2);
	wstring str = StringTool::UTF8_UTF16(buf1, 3);

}


void CStringToolDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	BYTE buf1[] = { -26, -79, -119 };
	BYTE buf2[128] = { 0 };
	int len1 = StringTool::UTF8_GB2312(buf1, 3, buf2);
	char ch[20] = { 0 };
	memcpy(ch, buf2, len1);
}
