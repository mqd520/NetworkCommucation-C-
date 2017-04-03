
// Client2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client2.h"
#include "Client2Dlg.h"
#include "afxdialogex.h"
#include "Protocol1Handle.h"

using namespace Protocol1;

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
}

BEGIN_MESSAGE_MAP(CClient2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
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



void CClient2Dlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CProtocol1Handle handler;
	//ҵ������
	char* str = "123";
	//ҵ������ת�ֽ�����
	BYTE* buf1 = (BYTE*)str;
	//���
	LPPackage1 pack1 = handler.Packet(Package1Type::type1, buf1, 4);
	//����
	BYTE* buf2 = handler.GetBuffer(pack1);
	//...

	//���
	int len = 11;
	LPPackage1 pack2 = handler.UnPacket(buf2, len);
	int datalen = handler.GetDataLen(pack2);
	BYTE buf3[1024];
	memcpy(buf3, pack2->data, datalen);

	delete buf2;
	handler.ReleaseMemory(pack2);
	handler.ReleaseMemory(pack1);
}
