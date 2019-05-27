
// Tool1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tool1.h"
#include "Tool1Dlg.h"
#include "afxdialogex.h"
#include "TimerAppMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTool1Dlg �Ի���

void OnTimer1(CTimer* pTimeout, int count);

CTool1Dlg::CTool1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTool1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTool1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTool1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTool1Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTool1Dlg ��Ϣ��������

BOOL CTool1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ����Ӷ���ĳ�ʼ������
	CTimerAppMgr::Init();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTool1Dlg::OnPaint()
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
HCURSOR CTool1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTool1Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������

	if (m_pTimer1 == NULL)
	{
		m_pTimer1 = new CTimer(1 * 1000, OnTimer1);
	}

	if (!m_pTimer1->IsRun())
	{
		m_pTimer1->Run();
	}

	if (m_pTimer2 == NULL)
	{
		m_pTimer2 = new CTimer(3 * 1000, OnTimer1);
	}

	if (!m_pTimer2->IsRun())
	{
		m_pTimer2->Run();
	}
}

void OnTimer1(CTimer* pTimeout, int count)
{
	SYSTEMTIME time;
	GetSystemTime(&time);

	wchar_t ch[1024] = { 0 };
	swprintf_s(ch, L"OnTimer1: count = %02d, time = %02d:%02d:%02d:%03d \n", count, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	OutputDebugString(ch);
}