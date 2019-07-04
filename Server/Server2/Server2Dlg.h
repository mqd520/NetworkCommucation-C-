
// Server2Dlg.h : 头文件
//

#pragma once


// CServer2Dlg 对话框
class CServer2Dlg : public CDialogEx
{
// 构造
public:
	CServer2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERVER2_DIALOG };

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnLog(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnConnectResult(WPARAM wParam, LPARAM lParam);

	void	ShowLog(CString log);

	// 实现
protected:
	// 服务端ip
	CEdit m_edIp;
	// 服务端端口
	CEdit m_edPort;
	CButton m_btnConnect;
	CButton m_btnClose;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
protected:
	// 日志
	CEdit m_edLog;
public:
	afx_msg void OnBnClickedButton3();
};
