
// Client3Dlg.h : ͷ�ļ�
//

#pragma once

#include <vector>

using namespace std;

// CClient3Dlg �Ի���
class CClient3Dlg : public CDialogEx
{
	// ����
public:
	CClient3Dlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_CLIENT3_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	LRESULT OnRecvData(WPARAM wparam, LPARAM lparam);
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
};
