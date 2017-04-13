
// Client2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client2.h"
#include "Client2Dlg.h"
#include "afxdialogex.h"
#include "NetTool.h"
#include "StringHandle.h"

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
	DDX_Control(pDX, IDC_EDIT1, m_edSend);
	DDX_Control(pDX, IDC_EDIT2, m_edResult);
	DDX_Text(pDX, IDC_EDIT1, m_strSend);
	DDX_Text(pDX, IDC_EDIT2, m_strResult);
}

BEGIN_MESSAGE_MAP(CClient2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClient2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClient2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CClient2Dlg::OnBnClickedButton3)
	ON_MESSAGE(WM_CUSTOM_MESSAGE1, &CClient2Dlg::OnRecvData)
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


void CClient2Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	string	str = UTF8ToMultiByte(m_strSend.GetBuffer());
	int len = 0;
	BYTE* buf = WriteMultiByteStr((char*)str.c_str(), &len);
	bool b = theApp.m_tcp.SendData(buf, len);
	delete buf;
	if (!b)
	{
		MessageBox(_T("����ʧ��!"));
	}
}


void CClient2Dlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	theApp.m_tcp.CloseConnect();
}


void CClient2Dlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	string	str = UTF8ToMultiByte(m_strSend.GetBuffer());
	int len = 0;
	BYTE* buf = WriteMultiByteStr((char*)str.c_str(), &len);
	theApp.m_tcp.SimulateServerData(buf, len);
	delete buf;
}

LRESULT CClient2Dlg::OnRecvData(WPARAM wparam, LPARAM lparam)
{
	UpdateData(true);
	string str = ReadMultiByteStr((BYTE*)wparam, (int)lparam);
	wstring wstr = MultiByteToUTF8(str.c_str());
	wstr += _T("\r\n");
	CString tmp(wstr.c_str());
	m_strResult = tmp + m_strResult;
	m_edResult.SetWindowText(m_strResult);
	return 0;
}
