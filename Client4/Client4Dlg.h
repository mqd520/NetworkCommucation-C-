
// Client4Dlg.h : ͷ�ļ�
//

#pragma once

#include "SocketAPI.h"

using namespace NetworkCommunication;


// CClient4Dlg �Ի���
class CClient4Dlg : public CDialogEx
{
// ����
public:
	CClient4Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT4_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CSocketMgr m_socket;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
