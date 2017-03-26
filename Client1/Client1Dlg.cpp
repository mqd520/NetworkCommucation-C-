
// Client1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client1.h"
#include "Client1Dlg.h"
#include "afxdialogex.h"
#include "TcpClient.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClient1Dlg �Ի���



CClient1Dlg::CClient1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClient1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CClient1Dlg::~CClient1Dlg()
{
	if (m_tcpClient)
	{
		delete m_tcpClient;
	}
}

void CClient1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST4, m_lc1);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
}

BEGIN_MESSAGE_MAP(CClient1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(TCPClientRecvMsg, OnTCPClientRecvMsg)
	ON_BN_CLICKED(IDC_BUTTON1, &CClient1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CClient1Dlg ��Ϣ�������

BOOL CClient1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_tcpClient = new CTcpClient(this->m_hWnd, _T("192.168.0.15"), 8011);
	m_lc1.InsertColumn(0, _T("Col1"), 0, 100);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE

}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClient1Dlg::OnPaint()
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
HCURSOR CClient1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClient1Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_tcpClient->StartConnect())
	{
		//MessageBox(_T("���ӳɹ�!"));
		m_btn1.EnableWindow(false);
	}
	else
	{
		//MessageBox(_T("����ʧ��!"));
	}
}

afx_msg LRESULT CClient1Dlg::OnTCPClientRecvMsg(WPARAM wParam, LPARAM lParam)
{
	char* str1 = (char*)wParam;
	char ch[3] = { '\0' };
	strncpy(ch, str1, 2);
	wchar_t* str = MultiByteToUTF8(ch);
	MessageBox(str);
	//int i = m_lc1.GetItemCount();
	//m_lc1.InsertItem(i, str);
	//delete str;
	return 0;
}
