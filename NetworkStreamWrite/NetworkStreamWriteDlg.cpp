
// NetworkStreamWriteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetworkStreamWrite.h"
#include "NetworkStreamWriteDlg.h"
#include "afxdialogex.h"
#include "nc/NetworkStreamWrite.h"

using namespace NetworkCommunication;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetworkStreamWriteDlg �Ի���



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
END_MESSAGE_MAP()


// CNetworkStreamWriteDlg ��Ϣ�������

BOOL CNetworkStreamWriteDlg::OnInitDialog()
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

void CNetworkStreamWriteDlg::OnPaint()
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
HCURSOR CNetworkStreamWriteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetworkStreamWriteDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������


}


void CNetworkStreamWriteDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CNetworkStreamWriteDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	BYTE buf1[128] = { 0 };
	CNetworkStreamWrite ns1(buf1, 128, EByteOrder::big);
	ns1.WriteShort(1);
	ns1.WriteShort(-1);
	int n1 = ns1.WritedCount();
	for (int i = 0; i < n1; i++)
	{
		char ch[10] = { 0 };
		sprintf_s(ch, "%d, ", buf1[i]);
		OutputDebugStringA(ch);
	}
	OutputDebugStringA("\n");


	BYTE buf2[128] = { 0 };
	CNetworkStreamWrite ns2(buf2, 128, EByteOrder::litte);
	ns2.WriteShort(1);
	ns2.WriteShort(-1);
	int n2 = ns2.WritedCount();
	for (int i = 0; i < n2; i++)
	{
		char ch[10] = { 0 };
		sprintf_s(ch, "%d, ", buf2[i]);
		OutputDebugStringA(ch);
	}
	OutputDebugStringA("\n");
}
