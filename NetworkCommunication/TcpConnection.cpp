#include "stdafx.h"
#include "TcpConnection.h"
#include "MemoryTool.h"
#include "Common.h"
#include "RecvPeerDataAction.h"
#include "NetCommuMgr.h"
#include "SendPeerDataResultAction.h"
#include "RecvPeerDataEvt.h"
#include "TcpDisconnectEvt.h"

namespace NetworkCommunication
{
	CTcpConnection::CTcpConnection(CTcpService* pSrv, SOCKET sendrecv) :
		m_pTcpSrv(pSrv),
		m_sendrecvSocket(sendrecv)
	{
		CNetworkCommuMgr::GetSelect()->AddSocket(sendrecv, ESelectSocketType::ReadWriteData);//����select����
	}

	CTcpConnection::~CTcpConnection()
	{

	}

	SOCKET CTcpConnection::GetSendRecvSocket()
	{
		return m_sendrecvSocket;
	}

	CTcpService* CTcpConnection::GetTcpService()
	{
		return m_pTcpSrv;
	}

	bool CTcpConnection::SendData(BYTE buf[], int len, int* actualLen)
	{
		int len1 = 0;//ʵ�ʷ��ͳ���
		bool result = m_socketAPI.Send(m_sendrecvSocket, buf, len, &len1);
		if (actualLen != NULL)
		{
			*actualLen = len1;
		}

		if (buf)
		{
			delete buf;
		}

		//�������ͽ������
		SendPeerDataResult* pData = new SendPeerDataResult();
		pData->success = result;
		pData->len = len;
		pData->actualLen = len1;
		CSendPeerDataResultAction* pAction = new CSendPeerDataResultAction(pData, m_sendrecvSocket);
		CNetworkCommuMgr::GetTcp()->PushTcpAction(pAction);

		return result;
	}

	void CTcpConnection::OnRecvPeerData(CRecvPeerDataAction* pAction)
	{
		CRecvPeerDataEvt* pEvent = new CRecvPeerDataEvt(m_pTcpSrv, m_sendrecvSocket, pAction->GetBuf(), pAction->GetLen());
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpEvent(pEvent);
	}

	void CTcpConnection::OnTcpDisconnect(int reason)
	{
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpEvent(new CTcpDisconnectEvt(reason, m_pTcpSrv, m_sendrecvSocket));
		CNetworkCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);//�Ƴ�ָ������(����)���ݵ�socket������tcp����
	}

	void CTcpConnection::OnSendDataCompleted(SendPeerDataResult* pResult)
	{
		if (!pResult->success)
		{
			CNetworkCommuMgr::GetSelect()->RemoveSocket(m_sendrecvSocket);//ɾ��select��ָ��socket
			CNetworkCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);//�Ƴ�ָ������(����)���ݵ�socket������tcp����
		}
	}

	void CTcpConnection::OnNetError()
	{
		CNetworkCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);//�Ƴ�ָ������(����)���ݵ�socket������tcp����
	}
}