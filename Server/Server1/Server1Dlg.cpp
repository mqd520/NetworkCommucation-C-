
// Server1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server1.h"
#include "Server1Dlg.h"
#include "afxdialogex.h"
#include "MSG.h"
#include "Def.h"

#include "tc/UTF16Str.h"

using namespace tc;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServer1Dlg �Ի���

CServer1Dlg::CServer1Dlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CServer1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServer1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edPort);
	DDX_Control(pDX, IDC_BUTTON1, m_btnListen);
	DDX_Control(pDX, IDC_LIST1, m_lcClients);
}

BEGIN_MESSAGE_MAP(CServer1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CServer1Dlg::OnBnClickedButton1)
	ON_MESSAGE(WM_USER_RECVCONN, &CServer1Dlg::OnRecvConn)
END_MESSAGE_MAP()


// CServer1Dlg ��Ϣ�������

BOOL CServer1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CString str = _T("8085");
	m_edPort.SetWindowText(str);

	m_lcClients.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_lcClients.InsertColumn(0, _T("���"), LVCFMT_CENTER, 50);
	m_lcClients.InsertColumn(1, _T("��ַ"), LVCFMT_CENTER, 180);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServer1Dlg::OnPaint()
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
HCURSOR CServer1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServer1Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	m_btnListen.EnableWindow(FALSE);

	CString str;
	m_edPort.GetWindowText(str);
	int port = 0;
	_stscanf_s(str, _T("%d"), &port);
	m_edPort.EnableWindow(FALSE);

	theApp.GetSrv1()->GetMainTcpSrv()->SetListenInfo(SocketTool::GetLocalIP(), port);
	bool b = theApp.GetSrv1()->GetMainTcpSrv()->Listen();
}

LRESULT CServer1Dlg::OnRecvConn(WPARAM wParam, LPARAM lParam)
{
	int id = wParam;

	ClientConnInfo info = theApp.GetSrv1()->GetClientConnInfoMgr()->GetInfo(id);
	if (info.ip != "")
	{
		CString str1;
		str1.Format(_T("%02d"), id + 1);
		CString str2;
		wstring str3 = UTF16Str::FromGB2312(info.ip);
		str2.Format(_T("%s:%d"), str3.c_str(), info.port);

		m_lcClients.InsertItem(id, str1.GetBuffer());
		m_lcClients.SetItemText(id, 1, str2.GetBuffer());
	}

	return 0;
}
