
// SocketToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SocketTool.h"
#include "SocketToolDlg.h"
#include "afxdialogex.h"

#include "tc/SocketTool.h"

using namespace tc;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSocketToolDlg �Ի���

void OnSocketErrorCallback(string err, void* lpParam);

CSocketToolDlg::CSocketToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocketToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSocketToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSocketToolDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSocketToolDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSocketToolDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSocketToolDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CSocketToolDlg ��Ϣ�������

BOOL CSocketToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	SocketTool::RegErrorCallback(OnSocketErrorCallback, this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSocketToolDlg::OnPaint()
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
HCURSOR CSocketToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketToolDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	bool b1 = SocketTool::Bind(0, SocketTool::GetLocalIP(), 0);
	bool b2 = SocketTool::Listen(0, SocketTool::GetLocalIP(), 0);
	SOCKET socket = SocketTool::Accept(0, SocketTool::GetLocalIP(), 0);
}

void OnSocketErrorCallback(string err, void* lpParam)
{
	OutputDebugStringA(err.c_str());
	OutputDebugStringA("\n");
}


void CSocketToolDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	bool b2 = SocketTool::Bind(0, "192.168.0.69", 0, false);
}


void CSocketToolDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	SocketTool::RemoveErrorCallback(OnSocketErrorCallback);
	bool b2 = SocketTool::Bind(0, "192.168.0.69", 0);
}


void CSocketToolDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	string ip = SocketTool::GetLocalIP();
	OutputDebugStringA(ip.c_str());
	OutputDebugStringA("\n");
}
