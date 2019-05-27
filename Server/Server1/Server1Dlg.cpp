
// Server1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server1.h"
#include "Server1Dlg.h"
#include "afxdialogex.h"
#include "tc/RecvNewConnEvt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServer1Dlg �Ի���

//************************************
// Method:    tcp�¼��ص�����
// Parameter: tcp�¼�����
// Parameter: ���Ӳ���
//************************************
void OnTcpEvt(TcpEvt* pEvt, void* pParam);

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
}

BEGIN_MESSAGE_MAP(CServer1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CServer1Dlg::OnBnClickedButton1)
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

	m_server.RegTcpEventCallback(OnTcpEvt, this);

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
	_tcscanf_s(_T("%d"), &port);
	m_edPort.EnableWindow(FALSE);
	
	m_server.Listen(_T("192.168.0.69"), port);
}

void OnTcpEvt(TcpEvt* pEvt, void* pParam)
{
	if (pEvt->GetEvtType() == ETcpEvt::RecvNewConn)
	{
		RecvNewConnEvt* pEvt1 = (RecvNewConnEvt*)pEvt;

		char ch[50] = { 0 };
		sprintf(ch, "recv new conn %s : %d \n", pEvt1->GetClientIP().c_str(), pEvt1->GetClientPort());

		OutputDebugStringA(ch);
	}
}
