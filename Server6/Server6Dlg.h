
// Server6Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CServer6Dlg �Ի���
class CServer6Dlg : public CDialogEx
{
	// ����
public:
	CServer6Dlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_SERVER6_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton2();
	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnRecvNewConnection(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRecvPeerData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPeerClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSendPeerDataResult(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRefuseNewConnection(WPARAM wParam, LPARAM lParam);
protected:
	void ShowLog(CString strLog);
protected:
	// �����IP�ؼ�
	CIPAddressCtrl m_ipServerIP;
	// ����˶˿ڿؼ�
	CEdit m_edServerPort;
	CButton m_btnListen;
	// �ͻ������ݿؼ�
	CListCtrl m_lcClientData;
	CButton m_btnSend;
protected:
	// ���������ı���
	CEdit m_editRecv;
	// �����ı���
	CEdit m_editSend;
};
