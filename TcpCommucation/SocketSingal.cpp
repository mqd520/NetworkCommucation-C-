#include "stdafx.h"
#include "SocketSingal.h"
#include "Common.h"
#include "NetCommuMgr.h"
#include "TcpConnectionMgr.h"
#include "ClientTcpConnection.h"
#include "RecvNewConnEvt.h"
#include "ConnectSrvResultEvt.h"

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
		if (type == ESelectSocketType::RecvConn)//ָʾsocket���ڽ��տͻ�������
		{
			RecvNewConnection(socket);
		}
		else if (type == ESelectSocketType::ReadWriteData)//ָʾsocket�����շ�����
		{
			RecvPeerData(socket);
		}
	}

	void CSocketSingal::ProcessWriteSingal(SOCKET socket, int type)
	{
		if (type == ESelectSocketType::ReadWriteData)//ָʾsocket�����շ�����
		{
			SendData(socket);
		}
		else if (type == ESelectSocketType::Connect)//ָʾsocket�������ӷ����
		{
			OnConnectSuccess(socket);
		}
	}

	void CSocketSingal::ProcessExceptSingal(SOCKET socket, int type)
	{
		if (type == ESelectSocketType::Connect)//ָʾsocket�������ӷ����
		{
			OnConnectFail(socket);
		}
	}

	void CSocketSingal::RecvNewConnection(SOCKET socket)
	{
		//��ȡ�����socket������tcp�������
		CTcpService* pSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			SOCKET client = m_socketAPI.Accept(socket, pSrv->GetServerIP(), pSrv->GetServerPort());
			if (client > 0)
			{
				CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new CRecvNewConnEvt(pSrv, client));
			}
		}
	}

	void CSocketSingal::RecvPeerData(SOCKET socket)
	{
		//��ȡtcp���Ӷ���
		CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
		if (pConn)
		{
			pConn->OnRecvPeerData();
		}
		else
		{
			CNetworkCommuMgr::GetSelect()->RemoveSocket(socket);
		}
	}

	void CSocketSingal::SendData(SOCKET socket)
	{
		CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
		if (pConn)
		{
			pConn->AsyncSendData();
		}
		else
		{
			CNetworkCommuMgr::GetSelect()->RemoveSocket(socket);//�Ƴ�select��ָ��socket
		}
	}

	void CSocketSingal::OnConnectSuccess(SOCKET socket)
	{
		//��ȡ�����socket������tcp�������
		CTcpService* pSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			//���ӳɹ���,������Ҫ�����Ƿ��������Ϸ����
			CNetworkCommuMgr::GetSelect()->RemoveSocket(socket, false);

			//������������¼�
			CConnectSrvResultEvt* pEvent = new CConnectSrvResultEvt(pSrv, true);
			CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);

			//����tcp����
			CClientTcpConnection* pConn = new CClientTcpConnection(pSrv, socket);
			CNetworkCommuMgr::GetTcpConnectionMgr()->PushTcpConn(pConn);

			//�ͻ���socket����ת��Ϊ�շ����ݵ�socket
			CNetworkCommuMgr::GetSelect()->AddSocket(socket, ESelectSocketType::ReadWriteData);
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
			if (CNetworkCommuMgr::IsExited())//ָʾ��Ҫ�˳�
			{
				break;//��������ѭ��,���ٴ������Ķ���
			}

			SocketSingalData data = m_queueSocketData.front();
			m_queueSocketData.pop();

			if (data.singaltype == SocketSingalType::Read)//����ɶ��ź�
			{
				ProcessReadSingal(data.socket, data.sockettype);
			}
			else if (data.singaltype == SocketSingalType::Write)//�����д�ź�
			{
				ProcessWriteSingal(data.socket, data.sockettype);
			}
			else if (data.singaltype == SocketSingalType::Except)//�����쳣�ź�
			{
				ProcessExceptSingal(data.socket, data.sockettype);
			}

			//֪ͨselect�㵱ǰsocket��ǰ�ź��Ѵ������
			CNetworkCommuMgr::GetSelect()->OnProcessingSocketCmp(data.socket, data.singaltype);
		}
	}
}