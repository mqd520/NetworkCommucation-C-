
// Tool1Dlg.h : 头文件
//

#pragma once

#include "Timer.h"

using namespace NetworkCommunication;


// CTool1Dlg 对话框
class CTool1Dlg : public CDialogEx
{
// 构造
public:
	CTool1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TOOL1_DIALOG };

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

private:
	CTimer* m_pTimer1;
	CTimer* m_pTimer2;

public:
	afx_msg void OnBnClickedOk();
};
