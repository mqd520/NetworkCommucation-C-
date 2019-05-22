
// Server1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "tc/TcpServer.h"

using namespace tc;

// CServer1Dlg �Ի���
class CServer1Dlg : public CDialogEx
{
// ����
public:
	CServer1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERVER1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �˿�
	CEdit m_edPort;
	// ������ť
	CButton m_btnListen;
	afx_msg void OnBnClickedButton1();

protected:
	CTcpServer m_server;
};
