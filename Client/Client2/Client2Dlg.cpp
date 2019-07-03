
// Client2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client2.h"
#include "Client2Dlg.h"
#include "afxdialogex.h"
#include "Msg.h"

#include "tc/SocketTool.h"
#include "tc/UTF16Str.h"
#include "tc/GB2312Str.h"
using namespace tc;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClient2Dlg �Ի���



CClient2Dlg::CClient2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClient2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClient2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edIp);
	DDX_Control(pDX, IDC_EDIT2, m_edPort);
	DDX_Control(pDX, IDC_BUTTON1, m_btnConnect);
	DDX_Control(pDX, IDC_BUTTON2, m_btnClose);
	DDX_Control(pDX, IDC_EDIT3, m_edLog);
}

BEGIN_MESSAGE_MAP(CClient2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_USER_LOGINFO, &CClient2Dlg::OnLog)
	ON_MESSAGE(WM_USER_CONNECTRESULT, &CClient2Dlg::OnConnectResult)
	ON_BN_CLICKED(IDC_BUTTON1, &CClient2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClient2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CClient2Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CClient2Dlg ��Ϣ�������

BOOL CClient2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	string strIp = SocketTool::GetLocalIP();
	wstring strIp1 = UTF16Str::FromGB2312(strIp);
	m_edIp.SetWindowText(strIp1.c_str());
	m_edPort.SetWindowText(_T("3000"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClient2Dlg::OnPaint()
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
HCURSOR CClient2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CClient2Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}

void CClient2Dlg::ShowLog(CString log)
{
	time_t t = time(NULL);
	tm t1;
	localtime_s(&t1, &t);

	CString originLog;
	m_edLog.GetWindowText(originLog);
	CString newLog;
	newLog.Format(_T("[%d-%02d-%02d %02d:%02d:%02d] %s \r\n%s"), t1.tm_year + 1900, t1.tm_mon, t1.tm_mday, t1.tm_hour, t1.tm_min, t1.tm_sec, log.GetString(), originLog.GetString());
	m_edLog.SetWindowText(newLog);
}

LRESULT CClient2Dlg::OnLog(WPARAM wParam, LPARAM lParam)
{
	char* str = (char*)wParam;
	wstring str1 = UTF16Str::FromGB2312(str);
	CString log;
	log.Format(_T("%s"), str1.c_str());
	ShowLog(log);

	return 0;
}

LRESULT CClient2Dlg::OnConnectResult(WPARAM wParam, LPARAM lParam)
{
	bool connected = wParam > 0 ? true : false;
	if (connected)
	{
		m_btnConnect.EnableWindow(FALSE);
		m_edIp.EnableWindow(FALSE);
		m_edPort.EnableWindow(FALSE);
	}
	else
	{
		m_btnConnect.EnableWindow(TRUE);
		m_edIp.EnableWindow(TRUE);
		m_edPort.EnableWindow(TRUE);
	}

	return 0;
}

void CClient2Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_btnConnect.EnableWindow(FALSE);
	m_edIp.EnableWindow(FALSE);
	m_edPort.EnableWindow(FALSE);

	CString str;
	m_edPort.GetWindowText(str);
	int port = 0;
	_stscanf_s(str, _T("%d"), &port);
	m_edPort.EnableWindow(FALSE);

	CString str1;
	m_edIp.GetWindowText(str1);
	string ip = GB2312Str::FromUTF16(str1.GetString());

	theApp.GetSrv1().GetSrvA().SetConnectInfo(ip, port);
	theApp.GetSrv1().GetSrvA().Connect();
}


void CClient2Dlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_btnConnect.EnableWindow(TRUE);
	m_edIp.EnableWindow(TRUE);
	m_edPort.EnableWindow(TRUE);

	//theApp.GetSrv1().GetSrvA().Close();
	//ShowLog(_T("user close the connection"));
}

void CClient2Dlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_edLog.SetWindowText(_T(""));
}
