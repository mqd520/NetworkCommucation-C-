
// Client8Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "NetworkStream.h"

using namespace NetworkCommunication;


// CClient8Dlg �Ի���
class CClient8Dlg : public CDialogEx
{
	// ����
public:
	CClient8Dlg(CWnd* pParent = NULL);	// ��׼���캯��

	~CClient8Dlg();

	// �Ի�������
	enum { IDD = IDD_CLIENT8_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	BYTE* m_pInputBuf;
	CNetworkStream* m_pNS;

protected:
	void ShowOperationBtn(bool show);//��ʾ��д������ť

	void ShowReadWriteByte();

	void ShowReadResult(CString str);

	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
protected:
	// �ֽ���ѡ��
	CButton m_cbByteOrder;
public:
	afx_msg void OnBnClickedButton17();
protected:
	CEdit m_edInputBuf;
	CButton m_btnCreate;
public:
	afx_msg void OnBnClickedButton18();
protected:
	CStatic m_edAvaiableRead;
	CStatic m_edAvaiableWrite;
	CEdit m_edOutput;
	CStatic m_edReadResult;
	CButton m_cbHex;
};
