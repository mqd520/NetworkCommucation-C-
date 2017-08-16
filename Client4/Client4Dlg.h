
// Client4Dlg.h : 头文件
//

#pragma once

#include "SocketAPI.h"

using namespace NetworkCommunication;


// CClient4Dlg 对话框
class CClient4Dlg : public CDialogEx
{
// 构造
public:
	CClient4Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENT4_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CSocketMgr m_socket;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
