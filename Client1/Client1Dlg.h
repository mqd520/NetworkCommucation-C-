
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
	LRESULT OnRecvData(WPARAM wparam, LPARAM lparam);
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
	CEdit m_edSend;//发送内容文本框
	CString m_strSend;//发送内容
	CButton m_btnSend;//发送按钮
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CEdit m_editResult;//结果文本框
	CString m_strResult;//结果
protected:
	// 模拟发送按钮
	CButton m_btnSimulate;
	// 模拟服务端数据发送
	CButton m_btnDisconnect;
};
