
// Tool1Dlg.h : ͷ�ļ�
//

#pragma once

#include "Timer.h"

using namespace NetworkCommunication;


// CTool1Dlg �Ի���
class CTool1Dlg : public CDialogEx
{
// ����
public:
	CTool1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TOOL1_DIALOG };

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

private:
	CTimer* m_pTimer1;
	CTimer* m_pTimer2;

public:
	afx_msg void OnBnClickedOk();
};
