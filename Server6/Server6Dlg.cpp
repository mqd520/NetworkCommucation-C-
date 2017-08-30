
// Server6Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server6.h"
#include "Server6Dlg.h"
#include "afxdialogex.h"
#include "MemoryTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServer6Dlg �Ի���



CServer6Dlg::CServer6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServer6Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServer6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipServerIP);
	DDX_Control(pDX, IDC_EDIT1, m_edServerPort);
	DDX_Control(pDX, IDC_BUTTON1, m_btnListen);
	DDX_Control(pDX, IDC_LIST1, m_lcClientData);
}

BEGIN_MESSAGE_MAP(CServer6Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CServer6Dlg::OnBnClickedButton1)
	ON_MESSAGE(WM_RECVNEWCONNECTION, &CServer6Dlg::OnRecvNewConnection)
END_MESSAGE_MAP()


// CServer6Dlg ��Ϣ�������

BOOL CServer6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_ipServerIP.SetWindowTextW(L"192.168.0.68");
	m_edServerPort.SetWindowTextW(L"8040");
	m_lcClientData.InsertColumn(0, _T("���"), LVCFMT_CENTER, 40, -1);
	m_lcClientData.InsertColumn(1, _T("�ͻ���IP"), LVCFMT_CENTER, 120, -1);
	m_lcClientData.InsertColumn(2, _T("�ͻ��˶˿�"), LVCFMT_CENTER, 80, -1);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServer6Dlg::OnPaint()
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
HCURSOR CServer6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServer6Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strServerIP, strServerPort;
	m_ipServerIP.GetWindowTextW(strServerIP);
	m_edServerPort.GetWindowTextW(strServerPort);
	int nServerPort = _wtoi(strServerPort.GetBuffer());

	if (nServerPort > 0)
	{
		theApp.m_tcpSrv.Listen(strServerIP.GetBuffer(), nServerPort);

		m_btnListen.EnableWindow(FALSE);
		m_edServerPort.EnableWindow(FALSE);
		m_ipServerIP.EnableWindow(FALSE);
	}
	else
	{
		MessageBoxW(L"��������ȷ��IP�Ͷ˿�", L"Title");
	}
}

LRESULT CServer6Dlg::OnRecvNewConnection(WPARAM wParam, LPARAM lParam)
{
	int index = (int)wParam;
	TcpSessionData session = theApp.m_sessionMgr.GetDataByIndex(index);
	CString strNumber, strPort;
	strNumber.Format(_T("%d"), index + 1);
	strPort.Format(_T("%d"), session.port);

	m_lcClientData.InsertItem(LVIF_TEXT | LVIF_STATE, index, strNumber.GetBuffer(), 0, 0, 0, 0);
	m_lcClientData.SetItemText(index, 1, session.ip);
	m_lcClientData.SetItemText(index, 2, strPort.GetBuffer());

	return 1;
}
