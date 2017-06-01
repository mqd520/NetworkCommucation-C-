#pragma once

#include "SocketMgr.h"
#include "TcpSessionMgr.h"

namespace NetworkCommunication
{
	//tcp�����
	class CTcpServer
	{
	protected:
		//�߳���Ϣ
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//�߳̾��
			DWORD dwThreadID;//�߳�ID
			bool bPause;//�Ƿ���ͣ
		}ThreadInfo, *LPThreadInfo;

	protected:
		CSocketMgr m_socketMgr;//socket�������
		TCHAR m_strServerIP[20];//�����IP
		int m_nServerPort;//����˶˿�
		bool m_bInited;//�Ƿ��ѳ�ʼ��
		SOCKET m_serverSocket;
		bool m_bListening;//�Ƿ����ڼ���
		ThreadInfo m_tiAccept;//���ܿͻ��������߳���Ϣ
		CTcpSessionMgr m_sessionMgr;//tcp�Ự����
		int m_nMaxConnectionCount;//�������ͻ������Ӽ���,0:������
		int m_nConnectedCount;//�����ӿͻ��˼���
		ThreadInfo m_tiSelect;//
		FD_SET m_fdRead;//

	protected:
		void CleanThread();

	public:
		CTcpServer();
		~CTcpServer();

		void Init(TCHAR* ip, int port, int maxConn = 0);
		void Listen();

		//����Ҫ����
		void StartAccept();
		void StartSelect();
	};
}