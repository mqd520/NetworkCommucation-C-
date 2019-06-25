
// Client1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CClient1Dlg �Ի���
class CClient1Dlg : public CDialogEx
{
	// ����
public:
	CClient1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_CLIENT1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnLog(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnConnectResult(WPARAM wParam, LPARAM lParam);

	void	ShowLog(CString log);

	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	// �����ip
	CEdit m_edIp;
	// ����˶˿�
	CEdit m_edPort;
	CButton m_btnConnect;
	CButton m_btnClose;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
protected:
	// ��־
	CEdit m_edLog;
};
