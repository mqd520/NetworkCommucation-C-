
// NetworkStreamReadDlg.h : 头文件
//

#pragma once


// CNetworkStreamReadDlg 对话框
class CNetworkStreamReadDlg : public CDialogEx
{
// 构造
public:
	CNetworkStreamReadDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NETWORKSTREAMREAD_DIALOG };

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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCancel2();
	afx_msg void OnBnClickedCancel3();
	afx_msg void OnBnClickedCancel4();
	afx_msg void OnBnClickedCancel5();
	afx_msg void OnBnClickedCancel6();
	afx_msg void OnBnClickedCancel7();
	afx_msg void OnBnClickedCancel8();
	afx_msg void OnBnClickedCancel9();
	afx_msg void OnBnClickedCancel10();
	afx_msg void OnBnClickedCancel11();
	afx_msg void OnBnClickedCancel12();
	afx_msg void OnBnClickedCancel13();
	afx_msg void OnBnClickedOk2();
};
