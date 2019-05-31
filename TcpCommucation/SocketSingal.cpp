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
	SocketSingalProcess::SocketSingalProcess()
	{

	}

	SocketSingalProcess::~SocketSingalProcess()
	{

	}

	void SocketSingalProcess::ProcessReadSingal(SOCKET socket, int type)
	{
		if (type == ESocketType::Accept)	// ָʾsocket���ڽ��տͻ�������
		{
			RecvNewConnection(socket);
		}
		else if (type == ESocketType::SendRecvData)	// ָʾsocket�����շ�����
		{
			RecvPeerData(socket);
		}
	}

	void SocketSingalProcess::ProcessWriteSingal(SOCKET socket, int type)
	{
		if (type == ESocketType::SendRecvData)	// ָʾsocket�����շ�����
		{
			SendData(socket);
		}
		else if (type == ESocketType::Connect)	// ָʾsocket�������ӷ����
		{
			OnConnectSuccess(socket);
		}
	}

	void SocketSingalProcess::ProcessExceptSingal(SOCKET socket, int type)
	{
		if (type == ESocketType::Connect)	// ָʾsocket�������ӷ����
		{
			OnConnectFail(socket);
		}
	}

	void SocketSingalProcess::RecvNewConnection(SOCKET socket)
	{
		// ��ȡ�����socket������tcp�������
		TcpService* pSrv = CTcpCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			//SOCKET client = m_socketAPI.Accept(socket, pSrv->GetSelfIP(), pSrv->GetSelfPort());
			//if (client > 0)
			//{
			//	CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new RecvNewConnEvt(pSrv, client));
			//}

			while (true)
			{
				SOCKET client = SocketTool::Accept(socket, pSrv->GetIP(), pSrv->GetPort(), false);
				if (client != INVALID_SOCKET)
				{
					CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new RecvNewConnEvt(pSrv, client));
				}
				else
				{
					break;
				}
			}
		}
	}

	void SocketSingalProcess::RecvPeerData(SOCKET socket)
	{
		// ��ȡtcp���Ӷ���
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

	void SocketSingalProcess::SendData(SOCKET socket)
	{
		CTcpConnection* pConn = CTcpCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
		if (pConn)
		{
			pConn->AsyncSendData();
		}
		else
		{
			CTcpCommuMgr::GetSelect()->RemoveSocket(socket);	// �Ƴ�select��ָ��socket
		}
	}

	void SocketSingalProcess::OnConnectSuccess(SOCKET socket)
	{
		// ��ȡ�����socket������tcp�������
		TcpService* pSrv = CTcpCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			// ���ӳɹ���,������Ҫ�����Ƿ��������Ϸ����
			CTcpCommuMgr::GetSelect()->RemoveSocket(socket, false);

			// ������������¼�
			ConnectSrvResultEvt* pEvent = new ConnectSrvResultEvt(pSrv, true);
			CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);

			// ����tcp����
			CClientTcpConnection* pConn = new CClientTcpConnection(pSrv, socket);
			CTcpCommuMgr::GetTcpConnectionMgr()->PushTcpConn(pConn);

			// �ͻ���socket����ת��Ϊ�շ����ݵ�socket
			CTcpCommuMgr::GetSelect()->AddSocket(socket, ESocketType::SendRecvData);
		}
	}

	void SocketSingalProcess::OnConnectFail(SOCKET socket)
	{

	}

	void SocketSingalProcess::PushSocket(SocketSingalData data)
	{
		quSignalSocketData.push(data);
	}

	bool SocketSingalProcess::IsEmpty()
	{
		return quSignalSocketData.size() == 0;
	}

	void SocketSingalProcess::ProcessSocketSingal()
	{
		while (quSignalSocketData.size() > 0)
		{
			if (CTcpCommuMgr::IsExited())	// ָʾ��Ҫ�˳�
			{
				break;	//��������ѭ��, ���ٴ������Ķ���
			}

			SocketSingalData data = quSignalSocketData.front();
			quSignalSocketData.pop();

			if (data.singaltype == ESocketSingalType::Read)	// ����ɶ��ź�
			{
				ProcessReadSingal(data.socket, data.sockettype);
			}
			else if (data.singaltype == ESocketSingalType::Write)	// �����д�ź�
			{
				ProcessWriteSingal(data.socket, data.sockettype);
			}
			else if (data.singaltype == ESocketSingalType::Except)	// �����쳣�ź�
			{
				ProcessExceptSingal(data.socket, data.sockettype);
			}

			// ֪ͨselect�㵱ǰsocket��ǰ�ź��Ѵ������
			CTcpCommuMgr::GetSelect()->OnProcessingSocketCmp(data.socket, data.singaltype);
		}
	}
}