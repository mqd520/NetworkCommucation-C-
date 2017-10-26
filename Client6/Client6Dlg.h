
// Client6Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Timeout.h"

using namespace NetworkCommunication;

// CClient6Dlg �Ի���
class CClient6Dlg : public CDialogEx
{
// ����
public:
	CClient6Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CClient6Dlg();

	void OnCustomTimer(CTimeout* pTimer, int count);

// �Ի�������
	enum { IDD = IDD_CLIENT6_DIALOG };

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
protected:
	CButton m_btn1;
	CButton m_btn2;
	CButton m_btn3;
	CButton m_btn4;
	CButton m_btn5;

protected:
	CTimeout* m_pTimer1;
	CTimeout* m_pTimer2;
	CTimeout* m_pTimer3;
	CTimeout* m_pTimer4;
	CTimeout* m_pTimer5;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
