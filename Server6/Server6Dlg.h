
// Server6Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CServer6Dlg 对话框
class CServer6Dlg : public CDialogEx
{
	// 构造
public:
	CServer6Dlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_SERVER6_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnRecvNewConnection(WPARAM wParam, LPARAM lParam);
protected:
	// 服务端IP控件
	CIPAddressCtrl m_ipServerIP;
	// 服务端端口控件
	CEdit m_edServerPort;
	CButton m_btnListen;
	// 客户端数据控件
	CListCtrl m_lcClientData;
};
