#include "stdafx.h"
#include "Include/tc/TcpCommuMgr.h"
#include "SocketAPI.h"

namespace tc
{
	volatile bool CTcpCommuMgr::m_bExited = false;

	CSelectThread CTcpCommuMgr::m_selectThread;
	CRecvThread CTcpCommuMgr::m_recvThread;
	CSendThread CTcpCommuMgr::m_sendThread;
	CCommonThread CTcpCommuMgr::m_commonThread;
	CTcpEvtThread CTcpCommuMgr::m_tcpEvtThread;

	CSelect CTcpCommuMgr::m_Select;
	CSocketSingal CTcpCommuMgr::m_otherSingal;
	CSocketSingal CTcpCommuMgr::m_recvSingal;
	CSocketSingal CTcpCommuMgr::m_sendSingal;

	CTcpConnectionMgr CTcpCommuMgr::m_tcpConnMgr;
	CTcpServiceMgr CTcpCommuMgr::m_tcpServiceMgr;
	CTcpEvtMgr CTcpCommuMgr::m_tcpEvtMgr;

	void CTcpCommuMgr::Init()
	{
		CSocketAPI::Init();
		GetSelectThread()->Run();//����select�߳�
		GetRecvThread()->Run();//�����������߳�
		GetSendThread()->Run();//�������������߳�
		GetCommonThread()->Run();//����ͨ���źŴ����߳�
		GetTcpEvtThread()->Run();//����tcp�¼��߳�
	}

	void CTcpCommuMgr::Exit()
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

	bool CTcpCommuMgr::IsExited()
	{
		return m_bExited;
	}

	CSelectThread* CTcpCommuMgr::GetSelectThread()
	{
		return &m_selectThread;
	}

	CRecvThread* CTcpCommuMgr::GetRecvThread()
	{
		return &m_recvThread;
	}

	CSendThread* CTcpCommuMgr::GetSendThread()
	{
		return &m_sendThread;
	}

	CCommonThread* CTcpCommuMgr::GetCommonThread()
	{
		return &m_commonThread;
	}

	CTcpEvtThread* CTcpCommuMgr::GetTcpEvtThread()
	{
		return &m_tcpEvtThread;
	}

	CSelect* CTcpCommuMgr::GetSelect()
	{
		return &m_Select;
	}

	CSocketSingal* CTcpCommuMgr::GetRecvDataSingal()
	{
		return &m_recvSingal;
	}

	CSocketSingal* CTcpCommuMgr::GetSendDataSingal()
	{
		return &m_sendSingal;
	}

	CSocketSingal* CTcpCommuMgr::GetOtherSingal()
	{
		return &m_otherSingal;
	}

	CTcpConnectionMgr* CTcpCommuMgr::GetTcpConnectionMgr()
	{
		return &m_tcpConnMgr;
	}

	CTcpServiceMgr* CTcpCommuMgr::GetTcpServiceMgr()
	{
		return &m_tcpServiceMgr;
	}

	CTcpEvtMgr* CTcpCommuMgr::GetTcpEvtMgr()
	{
		return &m_tcpEvtMgr;
	}
}