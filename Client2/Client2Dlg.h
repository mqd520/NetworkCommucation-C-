
// Client2Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CClient2Dlg �Ի���
class CClient2Dlg : public CDialogEx
{
// ����
public:
	CClient2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT2_DIALOG };

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
	// �����ı���
	CEdit m_edSend;
	// �ṹ�ı���
	CEdit m_edResult;
	CString m_strSend;//��������
	CString m_strResult;//���

	LRESULT OnRecvData(WPARAM wparam, LPARAM lparam);
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
