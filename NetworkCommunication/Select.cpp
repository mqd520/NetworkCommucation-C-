#include "stdafx.h"
#include "Select.h"
#include "TcpConnectionMgr.h"
#include "Thread.h"
#include "NetCommuMgr.h"
#include "Def.h"
#include "Common.h"

namespace NetworkCommunication
{
	void OnSelectThreadStart();

	CSelect::CSelect() :
		m_bExit(false),
		m_threadSelect(NULL),
		m_selectTimeout({ 0, 0 })
	{

	}

	CSelect::~CSelect()
	{
		if (m_threadSelect)
		{
			delete m_threadSelect;
		}
	}

	void CSelect::AddSocket(SOCKET socket, int type)
	{
		m_vecSocket.push_back({ socket, type });
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
		PrintfInfo("select thread started");
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
			Sleep(2 * 1000);//����ʱʹ��,������,��ע�͵�

			CalcSocketGroup();//��socket���з���

			if (m_group.size() > 0)
			{
				for (int i = 0; i < (int)m_group.size(); i++)
				{
					FD_ZERO(&m_readSet);

					for (int j = 0; j < (int)m_group[i].size(); j++)
					{
						FD_SET(m_group[i][j].socket, &m_readSet);
					}

					m_socketAPI.Select(0, &m_readSet, NULL, NULL, &m_selectTimeout);
					CNetworkCommuMgr::GetTcp()->OnServerSocketCanRead(m_group[i][0].socket);
					if (m_readSet.fd_count > 0)
					{
						//��������socket�����socket�ź�
						for (int k = 0; k < (int)m_group[i].size(); k++)
						{
							SelectSocketData socketData = m_group[i][k];
							CheckSocketSingal(socketData);
						}
					}
				}
			}
			else
			{
				Sleep(10);
			}
		}
	}

	void CSelect::CalcSocketGroup()
	{
		m_group.clear();

		int nSocketCount = (int)m_vecSocket.size();//socket����
		int nGroupCount = nSocketCount / FD_SETSIZE + (nSocketCount % FD_SETSIZE == 0 ? 0 : 1);//������
		for (int i = 0; i < nGroupCount; i++)
		{
			vector<SelectSocketData> vec;
			m_group.push_back(vec);
		}

		//��������socket
		for (int i = 0; i < (int)m_vecSocket.size(); i++)
		{
			int groupIndex = (i + 1) / FD_SETSIZE + ((i + 1) % FD_SETSIZE == 0 ? 0 : 1) - 1;//���㵱ǰsocket���ڷ�������
			m_group[groupIndex].push_back(m_vecSocket[i]);//��socket�����Ӧ������
		}
	}

	void CSelect::CheckSocketSingal(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &m_readSet);
		if (result > 0)
		{
			if (socketData.type == ESelectSocketType::RecvConn)//ָʾsocket���ڽ���������
			{
				CNetworkCommuMgr::GetTcp()->OnServerSocketCanRead(socketData.socket);
			}
			else//ָʾsocket���ڶ�д����
			{
				CNetworkCommuMgr::GetTcp()->OnReadWriteSocketCanRead(socketData.socket);
			}
		}
	}

	void CSelect::RemoveSocket(SOCKET socket)
	{
		for (vector<SelectSocketData>::iterator it = m_vecSocket.begin(); it < m_vecSocket.end(); it++)
		{
			if (it->socket == socket)
			{
				if (it->type == ESelectSocketType::ReadWriteData)
				{
					m_vecSocket.erase(it);
					//m_socketAPI.CloseSocket(socket);//�ر�socket
				}
				else
				{
					m_vecSocket.erase(it);
				}
				break;
			}
		}
	}
}