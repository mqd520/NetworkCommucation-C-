
// Client3Dlg.h : 头文件
//

#pragma once

#include <vector>

using namespace std;

// CClient3Dlg 对话框
class CClient3Dlg : public CDialogEx
{
	// 构造
public:
	CClient3Dlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_CLIENT3_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	LRESULT OnRecvData(WPARAM wparam, LPARAM lparam);
	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
