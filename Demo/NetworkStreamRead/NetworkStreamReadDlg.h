
// NetworkStreamReadDlg.h : ͷ�ļ�
//

#pragma once


// CNetworkStreamReadDlg �Ի���
class CNetworkStreamReadDlg : public CDialogEx
{
// ����
public:
	CNetworkStreamReadDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NETWORKSTREAMREAD_DIALOG };

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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCancel2();
	afx_msg void OnBnClickedCancel3();
	afx_msg void OnBnClickedCancel4();
	afx_msg void OnBnClickedCancel5();
	afx_msg void OnBnClickedCancel6();
	afx_msg void OnBnClickedCancel7();
	afx_msg void OnBnClickedCancel8();
	afx_msg void OnBnClickedCancel9();
	afx_msg void OnBnClickedCancel10();
	afx_msg void OnBnClickedCancel11();
	afx_msg void OnBnClickedCancel12();
	afx_msg void OnBnClickedCancel13();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
};