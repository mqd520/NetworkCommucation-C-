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
		if (type == ESelectSocketType::Accept)//ָʾsocket���ڽ��տͻ�������
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
		CTcpService* pSrv = CTcpCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			SOCKET client = m_socketAPI.Accept(socket, pSrv->GetServerIP(), pSrv->GetServerPort());
			if (client > 0)
			{
				CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new RecvNewConnEvt(pSrv, client, NULL, 0));
			}
		}
	}

	void CSocketSingal::RecvPeerData(SOCKET socket)
	{
		//��ȡtcp���Ӷ���
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
			CTcpCommuMgr::GetSelect()->RemoveSocket(socket);//�Ƴ�select��ָ��socket
		}
	}

	void CSocketSingal::OnConnectSuccess(SOCKET socket)
	{
		//��ȡ�����socket������tcp�������
		CTcpService* pSrv = CTcpCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			//���ӳɹ���,������Ҫ�����Ƿ��������Ϸ����
			CTcpCommuMgr::GetSelect()->RemoveSocket(socket, false);

			//������������¼�
			ConnectSrvResultEvt* pEvent = new ConnectSrvResultEvt(pSrv, true);
			CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);

			//����tcp����
			CClientTcpConnection* pConn = new CClientTcpConnection(pSrv, socket);
			CTcpCommuMgr::GetTcpConnectionMgr()->PushTcpConn(pConn);

			//�ͻ���socket����ת��Ϊ�շ����ݵ�socket
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
			if (CTcpCommuMgr::IsExited())//ָʾ��Ҫ�˳�
			{
				break;//��������ѭ��,���ٴ������Ķ���
			}

			SocketSingalData data = m_queueSocketData.front();
			m_queueSocketData.pop();

			if (data.singaltype == ESocketSingalType::Read)//����ɶ��ź�
			{
				ProcessReadSingal(data.socket, data.sockettype);
			}
			else if (data.singaltype == ESocketSingalType::Write)//�����д�ź�
			{
				ProcessWriteSingal(data.socket, data.sockettype);
			}
			else if (data.singaltype == ESocketSingalType::Except)//�����쳣�ź�
			{
				ProcessExceptSingal(data.socket, data.sockettype);
			}

			//֪ͨselect�㵱ǰsocket��ǰ�ź��Ѵ������
			CTcpCommuMgr::GetSelect()->OnProcessingSocketCmp(data.socket, data.singaltype);
		}
	}
}