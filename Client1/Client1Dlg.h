
// Client1Dlg.h : 头文件
//

#pragma once

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
	void OnRecvData(TCHAR* str);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//TCPClientRecvMsg消息响应
	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnBnClickedButton1();
protected:
	CListCtrl m_lc1;
	CButton m_btn1;
	CEdit m_edit1;
	CButton m_btn2;
	afx_msg void OnBnClickedButton2();
	CString m_str1;
	CString m_strServerIP;
	int m_nServerPort;
	CIPAddressCtrl m_ipServerIP;
	CEdit m_edServerPort;
	afx_msg void OnBnClickedButton3();
	CEdit m_editResult;
	CString m_strResult;
};
