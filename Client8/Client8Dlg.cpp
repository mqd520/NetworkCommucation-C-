
// Client8Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client8.h"
#include "Client8Dlg.h"
#include "afxdialogex.h"
#include <regex>
#include <string>
#include "MemoryTool.h"
#include <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClient8Dlg 对话框

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

int StrtoInt(char* str)
{
	int result = 0;
	if (str[0] >= 49 && str[0] <= 57)
	{
		sscanf_s(str, "%d", &result);
	}
	else
	{
		sscanf_s(str, "%x", &result);
	}
	return result;
}

CClient8Dlg::CClient8Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClient8Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CClient8Dlg::~CClient8Dlg()
{
	if (m_pNS)
	{
		delete m_pNS;
	}
	if (m_pInputBuf)
	{
		delete m_pInputBuf;
	}
}

void CClient8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_cbByteOrder);
	DDX_Control(pDX, IDC_EDIT1, m_edInputBuf);
	DDX_Control(pDX, IDC_BUTTON17, m_btnCreate);
	DDX_Control(pDX, IDC_STATIC5, m_edAvaiableRead);
	DDX_Control(pDX, IDC_STATIC7, m_edAvaiableWrite);
	DDX_Control(pDX, IDC_EDIT2, m_edOutput);
	DDX_Control(pDX, IDC_STATIC10, m_edReadResult);
	DDX_Control(pDX, IDC_CHECK2, m_cbHex);
}

BEGIN_MESSAGE_MAP(CClient8Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClient8Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClient8Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CClient8Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CClient8Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CClient8Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CClient8Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CClient8Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CClient8Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CClient8Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CClient8Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CClient8Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CClient8Dlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CClient8Dlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CClient8Dlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CClient8Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CClient8Dlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CClient8Dlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CClient8Dlg::OnBnClickedButton18)
END_MESSAGE_MAP()


// CClient8Dlg 消息处理程序

BOOL CClient8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_pNS = NULL;
	m_cbByteOrder.SetCheck(TRUE);
	m_cbHex.SetCheck(TRUE);
	ShowOperationBtn(true);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClient8Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClient8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClient8Dlg::ShowOperationBtn(bool show)
{
	if (show)
	{
		m_btnCreate.EnableWindow(TRUE);
		m_edInputBuf.EnableWindow(TRUE);
		m_cbByteOrder.EnableWindow(TRUE);
		m_cbHex.EnableWindow(TRUE);
	}
	else
	{
		m_btnCreate.EnableWindow(FALSE);
		m_edInputBuf.EnableWindow(FALSE);
		m_cbByteOrder.EnableWindow(FALSE);
		m_cbHex.EnableWindow(FALSE);
	}
}

void CClient8Dlg::ShowReadResult(CString str)
{
	m_edReadResult.SetWindowTextW(str);
}

void CClient8Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_pNS)
	{

	}
}


void CClient8Dlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_pNS && m_pNS->AvaliableRead() > 0)
	{
		BYTE b = m_pNS->ReadByte();
		ShowReadWriteByte();
		CString str;
		str.Format(_T("%d"), b);
		m_edReadResult.SetWindowTextW(str);
	}
}


void CClient8Dlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_pNS && m_pNS->AvaliableRead() > 0)
	{
		USHORT s = m_pNS->ReadUShort();
		ShowReadWriteByte();
		CString str;
		str.Format(_T("%d"), s);
		m_edReadResult.SetWindowTextW(str);
	}
}


void CClient8Dlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf[4] = { 0, 0, 1, 2 };
	CNetworkStream ns(buf, 4);
	UINT i = ns.ReadUInt();
}


void CClient8Dlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf[2] = { 1, 2 };
	CNetworkStream ns(buf, 2);
	UINT16 i = ns.ReadUInt16();
}


void CClient8Dlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf[8] = { 0, 0, 0, 0, 0, 0, 1, 2 };
	CNetworkStream ns(buf, 8);
	UINT64 i = ns.ReadUInt64();
}


void CClient8Dlg::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf[2] = { 254, 254 };
	CNetworkStream ns(buf, 2);
	short s = ns.ReadShort();
}


void CClient8Dlg::OnBnClickedButton8()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf[4] = { 255, 255, 254, 254 };
	CNetworkStream ns(buf, 4);
	int i = ns.ReadInt();
}


void CClient8Dlg::OnBnClickedButton9()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf[2] = { 254, 254 };
	CNetworkStream ns(buf, 2);
	INT16 i = ns.ReadInt16();
}


void CClient8Dlg::OnBnClickedButton10()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf[8] = { 255, 255, 255, 255, 255, 255, 254, 254 };
	CNetworkStream ns(buf, 8);
	INT64 i = ns.ReadInt64();
}


void CClient8Dlg::OnBnClickedButton11()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf[4] = { 195, 129, 12, 205 };
	CNetworkStream ns(buf, 4);
	float f2 = ns.ReadFloat();
	TRACE("%f \n", f2);
}


void CClient8Dlg::OnBnClickedButton12()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf[8] = { 192, 112, 33, 153, 153, 153, 153, 154 };
	CNetworkStream ns(buf, 8);
	double d = ns.ReadDouble();
	TRACE("%f \n", d);
}


void CClient8Dlg::OnBnClickedButton13()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf[4] = { 210, 187 };
	CNetworkStream ns(buf, 2);
	char ch[2];
	ns.ReadMultiByteStr(ch, 2);
}


void CClient8Dlg::OnBnClickedButton14()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf[2] = { 78, 0 };
	CNetworkStream ns(buf, 2);
	wchar_t ch[2] = { 0 };
	ns.ReadUTF16Str(ch, 2);
}


void CClient8Dlg::OnBnClickedButton15()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE buf[3] = { 228, 248, 128 };
	CNetworkStream ns(buf, 3);
	wchar_t ch[2] = { 1, 1 };
	ns.ReadUTF8Str(ch, 3);
}


void CClient8Dlg::OnBnClickedButton16()
{
	// TODO:  在此添加控件通知处理程序代码

}


void CClient8Dlg::OnBnClickedButton17()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_pInputBuf)
	{
		delete m_pInputBuf;
		m_pInputBuf = NULL;
	}

	int len = 0;

	CString str;
	m_edInputBuf.GetWindowTextW(str);
	if (str.GetLength() > 0)
	{
		string s = UTF8ToMultiByte(str.GetBuffer());
		vector<string> vec;
		SplitString(s, vec, " ");

		len = vec.size();
		m_pInputBuf = new BYTE[len];
		for (int i = 0; i < len; i++)
		{
			int val = 0;
			if (m_cbHex.GetCheck() >0)
			{
				sscanf_s((char*)vec[i].c_str(), "%02X", &val);
			}
			else
			{
				sscanf_s((char*)vec[i].c_str(), "%d", &val);
			}
			m_pInputBuf[i] = val % 256;
		}
	}

	if (m_pNS)
	{
		delete m_pNS;
		m_pNS = NULL;
	}
	m_pNS = new CNetworkStream(m_pInputBuf, len, m_cbByteOrder.GetCheck() == 1 ? true : false);
	ShowReadWriteByte();

	ShowOperationBtn(false);
}


void CClient8Dlg::OnBnClickedButton18()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_pNS)
	{
		delete m_pNS;
		m_pNS = NULL;
	}

	ShowOperationBtn(true);
}

void CClient8Dlg::ShowReadWriteByte()
{
	if (m_pNS)
	{
		CString read;
		read.Format(_T("%d"), m_pNS->AvaliableRead());
		m_edAvaiableRead.SetWindowTextW(read);

		CString write;
		write.Format(_T("%d"), m_pNS->AvaliableWrite());
		m_edAvaiableWrite.SetWindowTextW(write);

		CString str;
		for (int i = m_pNS->AvaliableReadIndex(); i < m_pNS->GetLen(); i++)
		{
			CString tmp;
			tmp.Format(_T("%02X "), m_pInputBuf[i]);
			str += tmp;
		}
		m_edOutput.SetWindowTextW(str);
	}
}
