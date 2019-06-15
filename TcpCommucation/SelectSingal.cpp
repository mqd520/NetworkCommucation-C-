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
		// ��ȡ�����socket������tcp�������
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
		// ��ȡtcp���Ӷ���
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
		// ��ȡ�����socket������tcp�������
		TcpService* pSrv = TcpCommu::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			//// ���ӳɹ���,������Ҫ�����Ƿ��������Ϸ����
			//CTcpCommuMgr::GetSelect()->RemoveSocket(socket, false);

			//// ������������¼�
			//ConnectSrvResultEvt* pEvent = new ConnectSrvResultEvt(pSrv, true);
			//CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);

			//// ����tcp����
			//CClientTcpConnection* pConn = new CClientTcpConnection(pSrv, socket);
			//CTcpCommuMgr::GetTcpConnectionMgr()->PushTcpConn(pConn);

			//// �ͻ���socket����ת��Ϊ�շ����ݵ�socket
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
			if (TcpCommu::IsExited())	// ָʾӦ�ó�����Ҫ�˳�
			{
				break;
			}

			SocketSingalData data = quSockets.front();
			assert(!quSockets.empty());
			quSockets.pop();

			if (data.singaltype == ESocketSingalType::Read)	// ����ɶ��ź�
			{
				if (data.sockettype == ESocketType::Accept)	// ָʾsocket���ڽ��տͻ�������
				{
					RecvNewConnection(data.socket);
				}
				else if (data.sockettype == ESocketType::SendRecvData)	// ָʾsocket�����շ�����
				{
					RecvPeerData(data.socket);
				}
			}
			else if (data.singaltype == ESocketSingalType::Except)	// �����쳣�ź�
			{
				if (data.sockettype == ESocketType::Connect)	// ָʾsocket�������ӷ����
				{

				}
			}

		}

		lock1.Unlock();
	}
}