
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
	void OnRecvData(TCHAR* str);
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
	CListCtrl m_lc1;
	CButton m_btn1;
	CEdit m_edit1;
	CButton m_btn2;
	afx_msg void OnBnClickedButton2();
	CString m_str1;
	CString m_strServerIP;
	int m_nServerPort;
	CIPAddressCtrl m_ipServerIP;
	CEdit m_edServerPort;
	afx_msg void OnBnClickedButton3();
	CEdit m_editResult;
	CString m_strResult;
};
