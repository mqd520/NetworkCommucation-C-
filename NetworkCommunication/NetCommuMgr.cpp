#include "stdafx.h"
#include "NetCommuMgr.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	volatile bool CNetworkCommuMgr::m_bExited = false;

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
		m_bExited = true;

		//退出线程
		GetSelectThread()->Exit();
		GetRecvThread()->Exit();
		GetSendThread()->Exit();
		GetCommonThread()->Exit();
		GetTcpEvtThread()->Exit();

		::Sleep(300);
	}

	void CNetworkCommuMgr::Release()
	{
		if (m_selectThread)
		{
			delete m_selectThread;
			m_selectThread = NULL;
		}
		if (m_Select)
		{
			delete m_Select;
			m_Select = NULL;
		}
		if (m_recvThread)
		{
			delete m_recvThread;
			m_recvThread = NULL;
		}
		if (m_recvSingal)
		{
			delete m_recvSingal;
			m_recvSingal = NULL;
		}
		if (m_sendThread)
		{
			delete m_sendThread;
			m_sendThread = NULL;
		}
		if (m_sendSingal)
		{
			delete m_sendSingal;
			m_sendSingal = NULL;
		}
		if (m_commonThread)
		{
			delete m_commonThread;
			m_commonThread = NULL;
		}
		if (m_commonSingal)
		{
			delete m_commonSingal;
			m_commonSingal = NULL;
		}
		if (m_commonThread)
		{
			delete m_commonThread;
			m_commonThread = NULL;
		}
		if (m_commonSingal)
		{
			delete m_commonSingal;
			m_commonSingal = NULL;
		}
		if (m_tcpEvtThread)
		{
			delete m_tcpEvtThread;
			m_tcpEvtThread = NULL;
		}
		if (m_tcpEvtMgr)
		{
			delete m_tcpEvtMgr;
			m_tcpEvtMgr = NULL;
		}
		if (m_tcpServiceMgr)
		{
			delete m_tcpServiceMgr;
			m_tcpServiceMgr = NULL;
		}
	}

	bool CNetworkCommuMgr::IsExited()
	{
		return m_bExited;
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