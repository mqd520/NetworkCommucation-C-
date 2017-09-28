#include "stdafx.h"
#include "NetCommuMgr.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	CThreadMgr* CNetworkCommuMgr::m_threadMgr = NULL;
	CSelectThread* CNetworkCommuMgr::m_selectThread = NULL;
	CRecvThread* CNetworkCommuMgr::m_recvThread = NULL;
	CSendThread* CNetworkCommuMgr::m_sendThread = NULL;
	CCommonThread* CNetworkCommuMgr::m_commonThread = NULL;
	CTcpEvtThread* CNetworkCommuMgr::m_tcpEvtThread = NULL;

	CSelect* CNetworkCommuMgr::m_Select = NULL;
	CCommonSingal* CNetworkCommuMgr::m_commonSingal = NULL;
	CRecvDataSingal* CNetworkCommuMgr::m_recvSingal = NULL;
	CSendDataSingal* CNetworkCommuMgr::m_sendSingal = NULL;

	CTcpConnectionMgr* CNetworkCommuMgr::m_tcpConnMgr = NULL;
	CTcpServiceMgr* CNetworkCommuMgr::m_tcpServiceMgr = NULL;
	CTcpEvtMgr* CNetworkCommuMgr::m_tcpEvtMgr = NULL;

	void CNetworkCommuMgr::Init()
	{
		CSocketAPI::Init();
		GetSelectThread()->Run();//启动select线程
		GetRecvThread()->Run();//启动收数据线程
		GetSendThread()->Run();//启动发送数据线程
		GetCommonThread()->Run();//启动通用信号处理线程
		GetTcpEvtThread()->Run();//启动tcp事件线程
	}

	void CNetworkCommuMgr::Exit()
	{
		CSocketAPI::Release();
		if (m_threadMgr)
		{
			delete m_threadMgr;
		}
		if (m_Select)
		{
			delete m_Select;
		}
	}

	CThreadMgr* CNetworkCommuMgr::GetThreadMgr()
	{
		if (m_threadMgr == NULL)
		{
			m_threadMgr = new CThreadMgr();
		}
		return m_threadMgr;
	}

	CSelectThread* CNetworkCommuMgr::GetSelectThread()
	{
		if (m_selectThread == NULL)
		{
			m_selectThread = new CSelectThread();
		}
		return m_selectThread;
	}

	CRecvThread* CNetworkCommuMgr::GetRecvThread()
	{
		if (m_recvThread == NULL)
		{
			m_recvThread = new CRecvThread();
		}
		return m_recvThread;
	}

	CSendThread* CNetworkCommuMgr::GetSendThread()
	{
		if (m_sendThread == NULL)
		{
			m_sendThread = new CSendThread();
		}
		return m_sendThread;
	}

	CCommonThread* CNetworkCommuMgr::GetCommonThread()
	{
		if (m_commonThread == NULL)
		{
			m_commonThread = new CCommonThread();
		}
		return m_commonThread;
	}

	CTcpEvtThread* CNetworkCommuMgr::GetTcpEvtThread()
	{
		if (m_tcpEvtThread == NULL)
		{
			m_tcpEvtThread = new CTcpEvtThread();
		}
		return m_tcpEvtThread;
	}

	CSelect* CNetworkCommuMgr::GetSelect()
	{
		if (m_Select == NULL)
		{
			m_Select = new CSelect();
		}
		return m_Select;
	}

	CRecvDataSingal* CNetworkCommuMgr::GetRecvDataSingal()
	{
		if (m_recvSingal == NULL)
		{
			m_recvSingal = new CRecvDataSingal();
		}
		return m_recvSingal;
	}

	CSendDataSingal* CNetworkCommuMgr::GetSendDataSingal()
	{
		if (m_sendSingal == NULL)
		{
			m_sendSingal = new CSendDataSingal();
		}
		return m_sendSingal;
	}

	CCommonSingal* CNetworkCommuMgr::GetCommonSingal()
	{
		if (m_commonSingal == NULL)
		{
			m_commonSingal = new CCommonSingal();
		}
		return m_commonSingal;
	}

	CTcpConnectionMgr* CNetworkCommuMgr::GetTcpConnectionMgr()
	{
		if (m_tcpConnMgr == NULL)
		{
			m_tcpConnMgr = new CTcpConnectionMgr();
		}
		return m_tcpConnMgr;
	}

	CTcpServiceMgr* CNetworkCommuMgr::GetTcpServiceMgr()
	{
		if (m_tcpServiceMgr == NULL)
		{
			m_tcpServiceMgr = new CTcpServiceMgr();
		}
		return m_tcpServiceMgr;
	}

	CTcpEvtMgr* CNetworkCommuMgr::GetTcpEvtMgr()
	{
		if (m_tcpEvtMgr == NULL)
		{
			m_tcpEvtMgr = new CTcpEvtMgr();
		}
		return m_tcpEvtMgr;
	}
}