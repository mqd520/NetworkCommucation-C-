
// Server1Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "tc/TcpServer.h"

using namespace tc;

// CServer1Dlg 对话框
class CServer1Dlg : public CDialogEx
{
// 构造
public:
	CServer1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERVER1_DIALOG };

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
public:
	// 端口
	CEdit m_edPort;
	// 监听按钮
	CButton m_btnListen;
	afx_msg void OnBnClickedButton1();

protected:
	CTcpServer m_server;
};
