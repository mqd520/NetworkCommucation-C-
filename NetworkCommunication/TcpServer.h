#pragma once

#include "SocketMgr.h"
#include "TcpConnectionMgr.h"
#include "Thread.h"
#include "NetCommuMgr.h"

namespace NetworkCommunication
{
	//tcp�����
	class CTcpServer
	{
	protected:
		CSocketMgr m_socketMgr;//socket�������
		TCHAR m_strServerIP[20];//�����IP
		int m_nServerPort;//����˶˿�
		bool m_bInited;//�Ƿ��ѳ�ʼ��
		SOCKET m_serverSocket;
		bool m_bListening;//�Ƿ����ڼ���
		CTcpConnectionMgr m_sessionMgr;//tcp�Ự����
		int m_nMaxConnectionCount;//�������ͻ������Ӽ���,0:������
		int m_nConnectedCount;//�����ӿͻ��˼���
		FD_SET m_fdRead;//

	public:
		CTcpServer();
		~CTcpServer();

		void Init(TCHAR* ip, int port, int maxConn = 0);
		bool Listen();
	};
}