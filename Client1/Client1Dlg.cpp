
// Client1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client1.h"
#include "Client1Dlg.h"
#include "afxdialogex.h"
#include "NetTool.h"
#include "Common.h"

using namespace NetTool;

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

}

void CClient1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
	DDX_Text(pDX, IDC_EDIT1, m_str1);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipServerIP);
	DDX_Control(pDX, IDC_EDIT2, m_edServerPort);
	DDX_Text(pDX, IDC_IPADDRESS1, m_strServerIP);
	DDX_Text(pDX, IDC_EDIT2, m_nServerPort);
	DDX_Control(pDX, IDC_EDIT3, m_editResult);
	DDX_Text(pDX, IDC_EDIT3, m_strResult);
}

BEGIN_MESSAGE_MAP(CClient1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClient1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClient1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CClient1Dlg::OnBnClickedButton3)
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
	TCHAR ip[20] = { '\0' };
	if (GetLocalIP(ip))
	{
		m_ipServerIP.SetWindowText(ip);
	}
	m_edServerPort.SetWindowText(_T("8080"));

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
	UpdateData(TRUE);
	if (theApp.ConnectServer(m_strServerIP.GetBuffer(), m_nServerPort))
	{
		m_btn1.EnableWindow(false);
		m_ipServerIP.EnableWindow(FALSE);
		m_edServerPort.EnableWindow(FALSE);
	}
}

void CClient1Dlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	int len = 0;
	BYTE* buf = WriteUTF8Str(m_str1.GetBuffer(), &len);
	if (!theApp.SendData(buf, len))
	{
		OnRecvData(_T("����ʧ��!"));
	}
}

void CClient1Dlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CClient1Dlg::OnRecvData(TCHAR* str)
{
	m_editResult.GetWindowText(m_strResult);
	m_strResult = _T("\r\n") + m_strResult;
	m_strResult = str + m_strResult;
	m_editResult.SetWindowTextW(m_strResult);
}