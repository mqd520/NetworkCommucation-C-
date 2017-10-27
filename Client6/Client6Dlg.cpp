
// Client6Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client6.h"
#include "Client6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClient6Dlg �Ի���

void OnTimer(CTimer* pTimer, int count);

CClient6Dlg::CClient6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClient6Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CClient6Dlg::~CClient6Dlg()
{
	if (m_pTimer1)
	{
		delete m_pTimer1;
	}
	if (m_pTimer2)
	{
		delete m_pTimer2;
	}
	if (m_pTimer3)
	{
		delete m_pTimer3;
	}
	if (m_pTimer4)
	{
		delete m_pTimer4;
	}
	if (m_pTimer5)
	{
		delete m_pTimer5;
	}
}

void CClient6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
	DDX_Control(pDX, IDC_BUTTON3, m_btn3);
	DDX_Control(pDX, IDC_BUTTON4, m_btn4);
	DDX_Control(pDX, IDC_BUTTON5, m_btn5);
}

BEGIN_MESSAGE_MAP(CClient6Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClient6Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClient6Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CClient6Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CClient6Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CClient6Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CClient6Dlg ��Ϣ�������

BOOL CClient6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_pTimer1 = new CTimer(1 * 1000, ::OnTimer);
	m_pTimer1->Run();
	m_pTimer2 = new CTimer(2 * 1000, ::OnTimer);
	m_pTimer2->Run();
	m_pTimer3 = new CTimer(3 * 1000, ::OnTimer);
	m_pTimer3->Run();
	m_pTimer4 = new CTimer(4 * 1000, ::OnTimer);
	m_pTimer4->Run();
	m_pTimer5 = new CTimer(5 * 1000, ::OnTimer);
	m_pTimer5->Run();



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClient6Dlg::OnPaint()
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
HCURSOR CClient6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClient6Dlg::OnCustomTimer(CTimer* pTimer, int count)
{
	if (pTimer == m_pTimer1)
	{
		CString str;
		m_btn1.GetWindowText(str);
		int n = _wtoi(str.GetBuffer());
		n += 1;
		str.Format(L"%d", n);
		m_btn1.SetWindowText(str);
	}
	else if (pTimer == m_pTimer2)
	{
		CString str;
		m_btn2.GetWindowText(str);
		int n = _wtoi(str.GetBuffer());
		n += 2;
		str.Format(L"%d", n);
		m_btn2.SetWindowText(str);
	}
	else if (pTimer == m_pTimer3)
	{
		CString str;
		m_btn3.GetWindowText(str);
		int n = _wtoi(str.GetBuffer());
		n += 3;
		str.Format(L"%d", n);
		m_btn3.SetWindowText(str);
	}
	else if (pTimer == m_pTimer4)
	{
		CString str;
		m_btn4.GetWindowText(str);
		int n = _wtoi(str.GetBuffer());
		n += 4;
		str.Format(L"%d", n);
		m_btn4.SetWindowText(str);
	}
	else if (pTimer == m_pTimer5)
	{
		CString str;
		m_btn5.GetWindowText(str);
		int n = _wtoi(str.GetBuffer());
		n += 5;
		str.Format(L"%d", n);
		m_btn5.SetWindowText(str);
	}
}

void OnTimer(CTimer* pTimer, int count)
{
	((CClient6Dlg*)theApp.m_pMainWnd)->OnCustomTimer(pTimer, count);
}



void CClient6Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_pTimer1->IsRun())
	{
		m_pTimer1->Pause();
	}
	else
	{
		m_pTimer1->Run(true);
	}
}


void CClient6Dlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_pTimer2->IsRun())
	{
		m_pTimer2->Pause();
	}
	else
	{
		m_pTimer2->Run(true);
	}
}


void CClient6Dlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_pTimer3->IsRun())
	{
		m_pTimer3->Pause();
	}
	else
	{
		m_pTimer3->Run(true);
	}
}


void CClient6Dlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_pTimer4->IsRun())
	{
		m_pTimer4->Pause();
	}
	else
	{
		m_pTimer4->Run(true);
	}
}


void CClient6Dlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_pTimer5->IsRun())
	{
		m_pTimer5->Pause();
	}
	else
	{
		m_pTimer5->Run(true);
	}
}
