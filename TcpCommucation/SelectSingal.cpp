#include "stdafx.h"
#include "SelectSingal.h"
#include "Common.h"
#include "Include/tc/TcpCommuMgr.h"
#include "TcpConnectionMgr.h"
#include "ClientTcpConnection.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "Include/tc/ConnectSrvResultEvt.h"
#include <assert.h>

namespace tc
{
	SelectSingal::SelectSingal()
	{

	}

	SelectSingal::~SelectSingal()
	{

	}

	void SelectSingal::RecvNewConnection(SOCKET socket)
	{
		// 获取服务端socket关联的tcp服务对象
		TcpService* pSrv = TcpCommu::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			while (true)
			{
				SOCKET client = SocketTool::Accept(socket, pSrv->GetIP(), pSrv->GetPort(), false);
				if (client != INVALID_SOCKET)
				{
					TcpCommu::GetTcpEvtMgr()->PushTcpEvent(new RecvNewConnEvt(pSrv, client));
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			SocketTool::ShutDown(socket);
			SocketTool::CloseSocket(socket);
		}
	}

	void SelectSingal::RecvPeerData(SOCKET socket)
	{
		// 获取tcp连接对象
		CTcpConnection* pConn = TcpCommu::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
		if (pConn)
		{
			pConn->OnRecvPeerData();
		}
		else
		{
			SocketTool::ShutDown(socket);
			SocketTool::CloseSocket(socket);
		}
	}

	void SelectSingal::SendData(SOCKET socket)
	{
		CTcpConnection* pConn = TcpCommu::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
		if (pConn)
		{
			pConn->AsyncSendData();
		}
		else
		{

		}
	}

	void SelectSingal::OnConnectSuccess(SOCKET socket)
	{
		// 获取服务端socket关联的tcp服务对象
		TcpService* pSrv = TcpCommu::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			//// 连接成功后,不再需要监听是否已连接上服务端
			//CTcpCommuMgr::GetSelect()->RemoveSocket(socket, false);

			//// 创建连接完成事件
			//ConnectSrvResultEvt* pEvent = new ConnectSrvResultEvt(pSrv, true);
			//CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);

			//// 建立tcp连接
			//CClientTcpConnection* pConn = new CClientTcpConnection(pSrv, socket);
			//CTcpCommuMgr::GetTcpConnectionMgr()->PushTcpConn(pConn);

			//// 客户端socket立刻转变为收发数据的socket
			//CTcpCommuMgr::GetSelect()->AddSocket(socket, ESocketType::SendRecvData);
		}
	}

	void SelectSingal::OnConnectFail(SOCKET socket)
	{

	}

	void SelectSingal::PushSocketSingal(SocketSingalData data)
	{
		lock1.Lock();

		/*bool b = false;
		for (vector<SocketSingalData>::iterator it = vecSockets.begin(); it != vecSockets.end(); it++)
		{
			if (it->socket == data.socket && it->singaltype == data.singaltype)
			{
				b = true;
				break;
			}
		}
		if (!b)
		{
			quSockets.push(data);
		}*/

		quSockets.push(data);

		lock1.Unlock();
	}

	bool SelectSingal::IsEmpty()
	{
		lock1.Lock();

		bool b = quSockets.size() == 0;

		lock1.Unlock();

		return b;
	}

	void SelectSingal::ProcessSocketSingal()
	{
		lock1.Lock();

		while (quSockets.size() > 0)
		{
			if (TcpCommu::IsExited())	// 指示应用程序需要退出
			{
				break;
			}

			SocketSingalData data = quSockets.front();
			assert(!quSockets.empty());
			quSockets.pop();

			if (data.singaltype == ESocketSingalType::Read)	// 处理可读信号
			{
				if (data.sockettype == ESocketType::Accept)	// 指示socket用于接收客户端连接
				{
					RecvNewConnection(data.socket);
				}
				else if (data.sockettype == ESocketType::SendRecvData)	// 指示socket用于收发数据
				{
					RecvPeerData(data.socket);
				}
			}
			else if (data.singaltype == ESocketSingalType::Except)	// 处理异常信号
			{
				if (data.sockettype == ESocketType::Connect)	// 指示socket用于连接服务端
				{

				}
			}

		}

		lock1.Unlock();
	}
}