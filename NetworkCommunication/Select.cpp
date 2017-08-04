#include "stdafx.h"
#include "Select.h"
#include "TcpConnectionMgr.h"
#include "Thread.h"
#include "NetCommuMgr.h"

namespace NetworkCommunication
{
	void OnSelectThreadStart();

	CSelect::CSelect() :
		m_bExit(false),
		m_threadSelect(NULL),
		m_bSleep(true)
	{

	}

	CSelect::~CSelect()
	{
		if (m_threadSelect)
		{
			delete m_threadSelect;
		}
	}

	void CSelect::AddListenSocket(SOCKET socket)
	{
		m_quListenSocket.push(socket);
		m_bSleep = false;
	}

	void CSelect::AddPeerSocket(SOCKET socket)
	{
		m_quPeerSocket.push(socket);
		m_bSleep = false;
	}

	void CSelect::Run()
	{
		if (m_threadSelect == NULL)
		{
			m_threadSelect = new CThread();
			m_threadSelect->SetCallback(OnSelectThreadStart);
			m_threadSelect->Start();
		}
	}

	void OnSelectThreadStart()
	{
		_tprintf(_T("Select thread started \n"));
		CNetworkCommuMgr::GetSelect()->ThreadEntry();
	}

	void CSelect::ThreadEntry()
	{
		StartSelect();
	}

	void CSelect::StartSelect()
	{
		while (true)
		{
			//Sleep(2 * 1000);

			fd_set readSet;
			FD_ZERO(&readSet);

			int readCount = 0;//可读socket计数

			if (CNetworkCommuMgr::GetSrvType() != CNetworkCommuMgr::EServiceType::Client)
			{
				//遍历服务端socket
				for (int i = 0; i < (int)m_quListenSocket.size(); i++)
				{
					SOCKET socket = m_quListenSocket.front();
					FD_SET(socket, &readSet);
					readCount++;
				}
			}

			//遍历对端socket
			for (int i = 0; i < (int)m_quPeerSocket.size(); i++)
			{
				SOCKET socket = m_quPeerSocket.front();
				FD_SET(socket, &readSet);
				readCount++;
			}

			timeval selectTimeout;
			selectTimeout.tv_sec = 0;
			selectTimeout.tv_usec = 0;

			m_socMgr.Select(0, &readSet, NULL, NULL, &selectTimeout);

			//遍历可读socket
			for (int i = 0; i < readCount; i++)
			{
				SOCKET socket = readSet.fd_array[i];
				int result = FD_ISSET(socket, &readSet);
				if (result > 0)
				{
					if (i == 0)
					{
						CNetworkCommuMgr::GetAccept()->OnRecvNewSocket(socket);//通知Accept层进行新连接的处理
					}
					else
					{
						CNetworkCommuMgr::GetTcpConnectionMgr()->OnSocketRead(socket);//通知TcpConnectionMgr层进行接收数据处理
					}
				}
			}

			if (m_bSleep)
			{
				Sleep(10);
			}
		}
	}
}