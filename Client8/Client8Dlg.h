
// Client8Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "NetworkStream.h"

using namespace NetworkCommunication;


// CClient8Dlg 对话框
class CClient8Dlg : public CDialogEx
{
	// 构造
public:
	CClient8Dlg(CWnd* pParent = NULL);	// 标准构造函数

	~CClient8Dlg();

	// 对话框数据
	enum { IDD = IDD_CLIENT8_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	BYTE* m_pInputBuf;
	CNetworkStream* m_pNS;

protected:
	void ShowOperationBtn(bool show);//显示读写操作按钮

	void ShowReadWriteByte();

	void ShowReadResult(CString str);

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
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
protected:
	// 字节序复选框
	CButton m_cbByteOrder;
public:
	afx_msg void OnBnClickedButton17();
protected:
	CEdit m_edInputBuf;
	CButton m_btnCreate;
public:
	afx_msg void OnBnClickedButton18();
protected:
	CStatic m_edAvaiableRead;
	CStatic m_edAvaiableWrite;
	CEdit m_edOutput;
	CStatic m_edReadResult;
	CButton m_cbHex;
};
