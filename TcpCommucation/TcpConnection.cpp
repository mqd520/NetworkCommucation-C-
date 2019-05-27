#include "stdafx.h"
#include "TcpConnection.h"
#include "MemoryTool.h"
#include "Common.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/RecvDataEvt.h"
#include "Include/tc/ConnDisconnectEvt.h"
#include "Include/tc/SendDataResultEvt.h"

namespace tc
{
	CTcpConnection::CTcpConnection(CTcpService* pSrv, SOCKET sendrecv) :
		m_pTcpSrv(pSrv),
		m_sendrecvSocket(sendrecv),
		m_pAsyncSendBuf(NULL),
		m_nAsyncSendLen(0),
		m_nAsyncSendStatus(EAsyncSendStatus::SendCmp),
		m_bCanAsyncSend(true)
	{
		CTcpCommuMgr::GetSelect()->AddSocket(sendrecv, ESelectSocketType::ReadWriteData);//����select����
	}

	CTcpConnection::~CTcpConnection()
	{
		if (m_pAsyncSendBuf)
		{
			delete m_pAsyncSendBuf;
		}
	}

	SOCKET CTcpConnection::GetSendRecvSocket()
	{
		return m_sendrecvSocket;
	}

	CTcpService* CTcpConnection::GetTcpService()
	{
		return m_pTcpSrv;
	}

	NetAddress CTcpConnection::GetLocalAddress()
	{
		return m_localAddress;
	}

	NetAddress CTcpConnection::GetPeerAddress()
	{
		return m_peerAddress;
	}

	void CTcpConnection::ProcessSendResult(bool success)
	{
		if (!success)
		{
			PrintfError(_T("Send data to %s:%d failed"), m_peerAddress.ip, m_peerAddress.port);
			OnConnDisconnect();
		}
	}

	bool CTcpConnection::SendData(BYTE* pBuf, int len, int* actualLen)
	{
		int len1 = 0;//ʵ�ʷ��ͳ���
		bool result = m_socketAPI.Send(m_sendrecvSocket, pBuf, len, &len1);

		if (actualLen != NULL)
		{
			*actualLen = len1;
		}

		ProcessSendResult(result);//���������ݽ��

		return result;
	}

	void CTcpConnection::SetAsyncSendData(BYTE* pBuf, int len, int* actualLen)
	{
		//�ȴ��������ڽ��еķ������ݶ���

		m_pAsyncSendBuf = new BYTE[len];
		memcpy(m_pAsyncSendBuf, pBuf, len);
		m_nAsyncSendLen = len;

		m_nAsyncSendStatus = EAsyncSendStatus::PreSend;
	}

	void CTcpConnection::AsyncSendData()
	{
		if (m_nAsyncSendStatus == EAsyncSendStatus::PreSend && m_pAsyncSendBuf && m_nAsyncSendLen > 0)
		{
			int len = 0;
			m_nAsyncSendStatus = EAsyncSendStatus::Sending;
			bool result = m_socketAPI.Send(m_sendrecvSocket, m_pAsyncSendBuf, m_nAsyncSendLen, &len);

			CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new SendDataResultEvt(m_pTcpSrv, result, m_nAsyncSendLen, len));

			delete m_pAsyncSendBuf;
			m_pAsyncSendBuf = NULL;
			m_nAsyncSendLen = 0;

			m_nAsyncSendStatus = EAsyncSendStatus::SendCmp;

			ProcessSendResult(result);
		}
	}

	void CTcpConnection::OnRecvPeerData()
	{
		BYTE* pRecvBuf = new BYTE[TC_TCPRECVBUFFERSIZE];
		int len = m_socketAPI.Recv(m_sendrecvSocket, pRecvBuf, TC_TCPRECVBUFFERSIZE);
		if (len > 0)//�������ݳɹ�
		{
			PrintfDebug(_T("[%s:%d][socket: %d] recved [%s:%d][socket: %d] data, size: %d"),
				m_localAddress.ip, m_localAddress.port, m_pTcpSrv->GetSocket(), m_peerAddress.ip, m_peerAddress.port, m_sendrecvSocket, len);

			RecvDataEvt* pEvent = new RecvDataEvt(m_pTcpSrv, m_sendrecvSocket, pRecvBuf, len);
			CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);
		}
		else//��������ʧ��
		{
			delete pRecvBuf;
			if (len == SOCKET_ERROR)//�������쳣
			{
				OnConnDisconnect();
			}
			else if (len == 0)//�Է��Ͽ�������
			{
				OnConnDisconnect();
			}
		}
	}

	void CTcpConnection::OnConnDisconnect()
	{
		CTcpCommuMgr::GetSelect()->RemoveSocket(m_sendrecvSocket);//�Ƴ�select������socket
		CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new ConnDisconnectEvt(m_pTcpSrv, m_sendrecvSocket));
		CTcpCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);//�Ƴ�tcp���Ӷ���
	}

	void CTcpConnection::OnNetError()
	{
		CTcpCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);//�Ƴ�ָ������(����)���ݵ�socket������tcp����
	}

	void CTcpConnection::Close()
	{
		CTcpCommuMgr::GetSelect()->RemoveSocket(m_sendrecvSocket);//�Ƴ�select������socket
		CTcpCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);//�Ƴ�tcp���Ӷ���
	}
}