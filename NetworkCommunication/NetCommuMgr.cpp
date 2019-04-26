#include "stdafx.h"
#include "NetCommuMgr.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	volatile bool CNetworkCommuMgr::m_bExited = false;

	CSelectThread CNetworkCommuMgr::m_selectThread;
	CRecvThread CNetworkCommuMgr::m_recvThread;
	CSendThread CNetworkCommuMgr::m_sendThread;
	CCommonThread CNetworkCommuMgr::m_commonThread;
	CTcpEvtThread CNetworkCommuMgr::m_tcpEvtThread;

	CSelect CNetworkCommuMgr::m_Select;
	CSocketSingal CNetworkCommuMgr::m_otherSingal;
	CSocketSingal CNetworkCommuMgr::m_recvSingal;
	CSocketSingal CNetworkCommuMgr::m_sendSingal;

	CTcpConnectionMgr CNetworkCommuMgr::m_tcpConnMgr;
	CTcpServiceMgr CNetworkCommuMgr::m_tcpServiceMgr;
	CTcpEvtMgr CNetworkCommuMgr::m_tcpEvtMgr;

	void CNetworkCommuMgr::Init()
	{
		CSocketAPI::Init();
		GetSelectThread()->Run();//����select�߳�
		GetRecvThread()->Run();//�����������߳�
		GetSendThread()->Run();//�������������߳�
		GetCommonThread()->Run();//����ͨ���źŴ����߳�
		GetTcpEvtThread()->Run();//����tcp�¼��߳�
	}

	void CNetworkCommuMgr::Exit()
	{
		m_bExited = true;

		//�˳��߳�
		GetSelectThread()->Exit();
		GetRecvThread()->Exit();
		GetSendThread()->Exit();
		GetCommonThread()->Exit();
		GetTcpEvtThread()->Exit();

#if RELEASE
		::Sleep(300);
#endif

		m_Select.Exit();
	}

	bool CNetworkCommuMgr::IsExited()
	{
		return m_bExited;
	}

	CSelectThread* CNetworkCommuMgr::GetSelectThread()
	{
		return &m_selectThread;
	}

	CRecvThread* CNetworkCommuMgr::GetRecvThread()
	{
		return &m_recvThread;
	}

	CSendThread* CNetworkCommuMgr::GetSendThread()
	{
		return &m_sendThread;
	}

	CCommonThread* CNetworkCommuMgr::GetCommonThread()
	{
		return &m_commonThread;
	}

	CTcpEvtThread* CNetworkCommuMgr::GetTcpEvtThread()
	{
		return &m_tcpEvtThread;
	}

	CSelect* CNetworkCommuMgr::GetSelect()
	{
		return &m_Select;
	}

	CSocketSingal* CNetworkCommuMgr::GetRecvDataSingal()
	{
		return &m_recvSingal;
	}

	CSocketSingal* CNetworkCommuMgr::GetSendDataSingal()
	{
		return &m_sendSingal;
	}

	CSocketSingal* CNetworkCommuMgr::GetOtherSingal()
	{
		return &m_otherSingal;
	}

	CTcpConnectionMgr* CNetworkCommuMgr::GetTcpConnectionMgr()
	{
		return &m_tcpConnMgr;
	}

	CTcpServiceMgr* CNetworkCommuMgr::GetTcpServiceMgr()
	{
		return &m_tcpServiceMgr;
	}

	CTcpEvtMgr* CNetworkCommuMgr::GetTcpEvtMgr()
	{
		return &m_tcpEvtMgr;
	}
}