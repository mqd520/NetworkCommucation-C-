
// Client1Dlg.h : ͷ�ļ�
//

#pragma once

#include "afxcmn.h"
#include "afxwin.h"

// CClient1Dlg �Ի���
class CClient1Dlg : public CDialogEx
{
	// ����
public:
	CClient1Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CClient1Dlg();

	// �Ի�������
	enum { IDD = IDD_CLIENT1_DIALOG };
	LRESULT OnRecvData(WPARAM wparam, LPARAM lparam);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//TCPClientRecvMsg��Ϣ��Ӧ
	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnBnClickedButton1();
protected:
	CEdit m_edSend;//���������ı���
	CString m_strSend;//��������
	CButton m_btnSend;//���Ͱ�ť
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CEdit m_editResult;//����ı���
	CString m_strResult;//���
protected:
	// ģ�ⷢ�Ͱ�ť
	CButton m_btnSimulate;
	// ģ���������ݷ���
	CButton m_btnDisconnect;
};
