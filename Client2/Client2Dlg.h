
// Client2Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CClient2Dlg 对话框
class CClient2Dlg : public CDialogEx
{
// 构造
public:
	CClient2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENT2_DIALOG };

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
	// 发送文本框
	CEdit m_edSend;
	// 结构文本框
	CEdit m_edResult;
	CString m_strSend;//发送内容
	CString m_strResult;//结果

	LRESULT OnRecvData(WPARAM wparam, LPARAM lparam);
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
