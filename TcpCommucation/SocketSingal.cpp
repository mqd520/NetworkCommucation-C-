#include "stdafx.h"
#include "SocketSingal.h"
#include "Common.h"
#include "Include/tc/TcpCommuMgr.h"
#include "TcpConnectionMgr.h"
#include "ClientTcpConnection.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "Include/tc/ConnectSrvResultEvt.h"

namespace tc
{
	CSocketSingal::CSocketSingal()
	{

	}

	CSocketSingal::~CSocketSingal()
	{

	}

	void CSocketSingal::ProcessReadSingal(SOCKET socket, int type)
	{
		if (type == ESelectSocketType::Accept)//指示socket用于接收客户端连接
		{
			RecvNewConnection(socket);
		}
		else if (type == ESelectSocketType::ReadWriteData)//指示socket用于收发数据
		{
			RecvPeerData(socket);
		}
	}

	void CSocketSingal::ProcessWriteSingal(SOCKET socket, int type)
	{
		if (type == ESelectSocketType::ReadWriteData)//指示socket用于收发数据
		{
			SendData(socket);
		}
		else if (type == ESelectSocketType::Connect)//指示socket用于连接服务端
		{
			OnConnectSuccess(socket);
		}
	}

	void CSocketSingal::ProcessExceptSingal(SOCKET socket, int type)
	{
		if (type == ESelectSocketType::Connect)//指示socket用于连接服务端
		{
			OnConnectFail(socket);
		}
	}

	void CSocketSingal::RecvNewConnection(SOCKET socket)
	{
		//获取服务端socket关联的tcp服务对象
		TcpService* pSrv = CTcpCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			//SOCKET client = m_socketAPI.Accept(socket, pSrv->GetSelfIP(), pSrv->GetSelfPort());
			//if (client > 0)
			//{
			//	CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new RecvNewConnEvt(pSrv, client));
			//}
		}
	}

	void CSocketSingal::RecvPeerData(SOCKET socket)
	{
		//获取tcp连接对象
		CTcpConnection* pConn = CTcpCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
		if (pConn)
		{
			pConn->OnRecvPeerData();
		}
		else
		{
			CTcpCommuMgr::GetSelect()->RemoveSocket(socket);
		}
	}

	void CSocketSingal::SendData(SOCKET socket)
	{
		CTcpConnection* pConn = CTcpCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
		if (pConn)
		{
			pConn->AsyncSendData();
		}
		else
		{
			CTcpCommuMgr::GetSelect()->RemoveSocket(socket);//移除select中指定socket
		}
	}

	void CSocketSingal::OnConnectSuccess(SOCKET socket)
	{
		//获取服务端socket关联的tcp服务对象
		TcpService* pSrv = CTcpCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			//连接成功后,不再需要监听是否已连接上服务端
			CTcpCommuMgr::GetSelect()->RemoveSocket(socket, false);

			//创建连接完成事件
			ConnectSrvResultEvt* pEvent = new ConnectSrvResultEvt(pSrv, true);
			CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);

			//建立tcp连接
			CClientTcpConnection* pConn = new CClientTcpConnection(pSrv, socket);
			CTcpCommuMgr::GetTcpConnectionMgr()->PushTcpConn(pConn);

			//客户端socket立刻转变为收发数据的socket
			CTcpCommuMgr::GetSelect()->AddSocket(socket, ESelectSocketType::ReadWriteData);
		}
	}

	void CSocketSingal::OnConnectFail(SOCKET socket)
	{

	}

	void CSocketSingal::PushSocket(SocketSingalData data)
	{
		m_queueSocketData.push(data);
	}

	bool CSocketSingal::IsEmpty()
	{
		return m_queueSocketData.size() == 0;
	}

	void CSocketSingal::ProcessSocketSingal()
	{
		while (m_queueSocketData.size() > 0)
		{
			if (CTcpCommuMgr::IsExited())//指示需要退出
			{
				break;//立刻跳出循环,不再处理后面的队列
			}

			SocketSingalData data = m_queueSocketData.front();
			m_queueSocketData.pop();

			if (data.singaltype == ESocketSingalType::Read)//处理可读信号
			{
				ProcessReadSingal(data.socket, data.sockettype);
			}
			else if (data.singaltype == ESocketSingalType::Write)//处理可写信号
			{
				ProcessWriteSingal(data.socket, data.sockettype);
			}
			else if (data.singaltype == ESocketSingalType::Except)//处理异常信号
			{
				ProcessExceptSingal(data.socket, data.sockettype);
			}

			//通知select层当前socket当前信号已处理完毕
			CTcpCommuMgr::GetSelect()->OnProcessingSocketCmp(data.socket, data.singaltype);
		}
	}
}