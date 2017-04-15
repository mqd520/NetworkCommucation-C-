
// Client3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client3.h"
#include "Client3Dlg.h"
#include "afxdialogex.h"
#include "NetTool.h"
#include "StringHandle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClient3Dlg �Ի���

CClient3Dlg::CClient3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClient3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClient3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClient3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClient3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClient3Dlg::OnBnClickedButton2)
	ON_MESSAGE(WM_CUSTOM_MESSAGE1, &CClient3Dlg::OnRecvData)
END_MESSAGE_MAP()


// CClient3Dlg ��Ϣ�������

BOOL CClient3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClient3Dlg::OnPaint()
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
HCURSOR CClient3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClient3Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DemoPackage1 packet1;
	packet1.strUsername = _T("eguser001");
	packet1.strPwd = _T("123456");
	theApp.m_demoProtocol.SimulateServerData(DemoPackageType::type1, &packet1);
}


void CClient3Dlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DemoPackage1 packet1;
	packet1.strUsername = _T("eguser001");
	packet1.strPwd = _T("123456");
	theApp.m_demoProtocol.SendData(DemoPackageType::type1, &packet1);
}

LRESULT CClient3Dlg::OnRecvData(WPARAM wparam, LPARAM lparam)
{
	UpdateData(true);
	return 0;
}