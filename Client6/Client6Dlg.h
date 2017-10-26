
// Client6Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Timeout.h"

using namespace NetworkCommunication;

// CClient6Dlg 对话框
class CClient6Dlg : public CDialogEx
{
// 构造
public:
	CClient6Dlg(CWnd* pParent = NULL);	// 标准构造函数
	~CClient6Dlg();

	void OnCustomTimer(CTimeout* pTimer, int count);

// 对话框数据
	enum { IDD = IDD_CLIENT6_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
