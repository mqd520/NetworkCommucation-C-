
// Server6Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server6.h"
#include "Server6Dlg.h"
#include "afxdialogex.h"
#include "MemoryTool.h"
#include "NetworkStream.h"

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
	DDX_Control(pDX, IDC_BUTTON2, m_btnSend);
	DDX_Control(pDX, IDC_EDIT2, m_editRecv);
	DDX_Control(pDX, IDC_EDIT3, m_editSend);
}

BEGIN_MESSAGE_MAP(CServer6Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CServer6Dlg::OnBnClickedButton1)
	ON_MESSAGE(WM_RECVNEWCONNECTION, &CServer6Dlg::OnRecvNewConnection)
	ON_BN_CLICKED(IDC_BUTTON2, &CServer6Dlg::OnBnClickedButton2)
	ON_MESSAGE(WM_RECVPEERDATA, &CServer6Dlg::OnRecvPeerData)
	ON_MESSAGE(WM_PEERCLOSE, &CServer6Dlg::OnPeerClose)
	ON_MESSAGE(WM_SENDPEERDATARESULT, &CServer6Dlg::OnSendPeerDataResult)
	ON_MESSAGE(WM_REFUSENEWCONNECTION, &CServer6Dlg::OnRefuseNewConnection)
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

	//��ʼ��listctrl
	DWORD dwStyle = m_lcClientData.GetStyle();
	dwStyle |= LVS_SHOWSELALWAYS;
	SetWindowLong(m_lcClientData.m_hWnd, GWL_STYLE, dwStyle);
	DWORD dwExStyle = m_lcClientData.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT;//ѡ������
	dwExStyle |= LVS_EX_GRIDLINES;//��ʾ������
	m_lcClientData.SetExtendedStyle(dwExStyle);
	m_lcClientData.InsertColumn(0, _T("���"), LVCFMT_CENTER, 40, -1);
	m_lcClientData.InsertColumn(1, _T("�ͻ���IP"), LVCFMT_CENTER, 120, -1);
	m_lcClientData.InsertColumn(2, _T("�ͻ��˶˿�"), LVCFMT_CENTER, 80, -1);

	//m_lcClientData.InsertItem(LVIF_TEXT | LVIF_STATE, 0, _T("1"), 0, 0, 0, 0);
	//m_lcClientData.SetItemText(0, 1, _T("192.168.0.68"));
	//m_lcClientData.SetItemText(0, 2, _T("8040"));

	//m_lcClientData.InsertItem(LVIF_TEXT | LVIF_STATE, 1, _T("2"), 0, 0, 0, 0);
	//m_lcClientData.SetItemText(1, 1, _T("192.168.0.69"));
	//m_lcClientData.SetItemText(1, 2, _T("8041"));

	//m_lcClientData.InsertItem(LVIF_TEXT | LVIF_STATE, 2, _T("3"), 0, 0, 0, 0);
	//m_lcClientData.SetItemText(2, 1, _T("192.168.0.66"));
	//m_lcClientData.SetItemText(2, 2, _T("8042"));

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
		m_btnSend.ShowWindow(SW_SHOW);
		ShowLog(_T("Listen success"));
	}
	else
	{
		MessageBoxW(L"��������ȷ��IP�Ͷ˿�", L"Title");
	}
}

LRESULT CServer6Dlg::OnRecvNewConnection(WPARAM wParam, LPARAM lParam)
{
	int index = (int)wParam;
	int lcNewIndex = m_lcClientData.GetItemCount();

	TcpSessionData session = theApp.m_sessionMgr.GetDataByIndex(index);
	CString strNumber, strPort;
	strNumber.Format(_T("%d"), lcNewIndex + 1);
	strPort.Format(_T("%d"), session.port);

	m_lcClientData.InsertItem(LVIF_TEXT | LVIF_STATE, lcNewIndex, strNumber.GetBuffer(), 0, 0, 0, 0);
	m_lcClientData.SetItemText(lcNewIndex, 1, session.ip);
	m_lcClientData.SetItemText(lcNewIndex, 2, strPort.GetBuffer());

	CString str;
	str.Format(_T("Recv a new client: %s:%d"), session.ip, session.port);
	ShowLog(str);

	return 0;
}

void CServer6Dlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int index = -1;
	for (int i = 0; i < m_lcClientData.GetItemCount(); i++)
	{
		UINT state = m_lcClientData.GetItemState(i, LVIS_SELECTED);
		if (state == LVIS_SELECTED)
		{
			index = i;
		}
	}

	if (index > -1)
	{
		TcpSessionData session = theApp.m_sessionMgr.GetDataByIndex(index);
		CString strSend;
		m_editSend.GetWindowTextW(strSend);
		string str = UTF8ToMultiByte(strSend.GetBuffer());
		int len = 0;
		BYTE* buf = WriteMultiByteStr((char*)str.c_str(), &len);
		CString log;
		log.Format(_T("Prepare Send data to %s:%d, size: %d"), session.ip, session.port, len);
		ShowLog(log);

		bool b = theApp.m_tcpSrv.SendData(session.client, buf, len, false);
		//theApp.m_tcpSrv.SendData(session.client, buf, len);

		delete buf;
	}
}

LRESULT CServer6Dlg::OnRecvPeerData(WPARAM wParam, LPARAM lParam)
{
	PeerData* pData = (PeerData*)wParam;
	if (pData)
	{
		CString str;
		CNetworkStream ns;
		ns.Write(pData->buf, pData->len);
		string strData = ns.ReadMultiStr(pData->len);
		wstring wstrData = MultiByteToUTF8(strData.c_str());
		str.Format(_T("Recv data from %s:%d, size: %d, data(string): %s \n"), pData->ip, pData->port, pData->len, wstrData.c_str());
		ShowLog(str);
	}
	return 0;
}

LRESULT CServer6Dlg::OnPeerClose(WPARAM wParam, LPARAM lParam)
{
	int index = (int)wParam;
	if (index > -1 && index < m_lcClientData.GetItemCount())
	{
		m_lcClientData.DeleteItem(index);
	}
	return 0;
}

LRESULT CServer6Dlg::OnSendPeerDataResult(WPARAM wParam, LPARAM lParam)
{
	SendPeerDataResult* pResult = (SendPeerDataResult*)wParam;
	if (pResult)
	{
		CString str;
		if (pResult)
		{
			str.Format(_T("Send data to %s:%d success,size: %d \n"), pResult->ip, pResult->port, pResult->len);
		}
		else
		{

		}
		ShowLog(str);
	}
	return 0;
}

void CServer6Dlg::ShowLog(CString strLog)
{
	CString log, newLog;
	m_editRecv.GetWindowTextW(log);
	newLog = strLog + _T("\r\n") + log;
	m_editRecv.SetWindowTextW(newLog);
}

LRESULT CServer6Dlg::OnRefuseNewConnection(WPARAM wParam, LPARAM lParam)
{
	TCHAR* ip = (TCHAR*)wParam;
	CString str;
	str.Format(_T("Server refuse a new connection: %s:%d"), ip, lParam);
	ShowLog(str);
	return 0;
}
