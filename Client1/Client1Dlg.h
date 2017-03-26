
// Client1Dlg.h : 头文件
//

#pragma once

#include "TcpClient.h"
#include "afxcmn.h"
#include "afxwin.h"

// CClient1Dlg 对话框
class CClient1Dlg : public CDialogEx
{
	// 构造
public:
	CClient1Dlg(CWnd* pParent = NULL);	// 标准构造函数
	~CClient1Dlg();

	// 对话框数据
	enum { IDD = IDD_CLIENT1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	CTcpClient* m_tcpClient;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnTCPClientRecvMsg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
protected:
	CListCtrl m_lc1;
public:
	CButton m_btn1;
};
