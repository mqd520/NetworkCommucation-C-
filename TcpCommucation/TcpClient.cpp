#include "stdafx.h"
#include "TcpClient.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/ConnectSrvResultEvt.h"
#include "MemoryTool.h"

namespace tc
{
	TcpClient::TcpClient(string ip /*= ""*/, int port /*= 0*/) :
		TcpService(ip, port),
		bIsConnecting(false),
		bIsConnected(false)
	{

	}

	TcpClient::~TcpClient()
	{

	}

	void TcpClient::Init()
	{
		//		if (socket == INVALID_SOCKET)
		//		{
		//			socket = m_socketAPI.CreateTcpSocket();
		//			SOCKADDR_IN addr;
		//			addr.sin_family = AF_INET;
		//			addr.sin_port = htons(nSelfPort);
		//#ifdef _UNICODE
		//			string str = UTF8ToMultiByte(strSelfIP);
		//			addr.sin_addr.S_un.S_addr = inet_addr(str.c_str());
		//#else
		//			addr.sin_addr.S_un.S_addr = inet_addr(strSelfIP);
		//#endif // _UNICODE
		//			m_socketAPI.SetNonBlock(socket);
		//
		//			CTcpCommuMgr::GetSelect()->AddSocket(socket, ESelectSocketType::Connect);
		//		}
	}

	void TcpClient::Reconnect()
	{
		//û�����ڽ�������,û�������Ϸ���˵�ʱ����ܽ�������
		if (!bIsConnecting && !bIsConnected)
		{
			bIsConnecting = true;
			//m_socketAPI.Connect1(socket, strSelfIP, nSelfPort);
		}
	}

	void TcpClient::Connect()
	{
		Init();
		Reconnect();
	}

	bool TcpClient::Send(BYTE* pBuf, int len, bool asyncs/* = true*/, int* actualLen/* = NULL*/)
	{
		return __super::SendData(socket, pBuf, len, asyncs, actualLen);
	}

	void TcpClient::OnRecvTcpEvent(TcpEvt* pEvent)
	{
		__super::OnRecvTcpEvent(pEvent);

		if (pEvent->GetEvtType() == ETcpEvt::ConnectSrvResult)
		{
			bIsConnecting = false;	//���������
			ConnectSrvResultEvt* pConnCmpEvt = (ConnectSrvResultEvt*)pEvent;
			bIsConnected = pConnCmpEvt->GetConnectResult();
		}
	}
}