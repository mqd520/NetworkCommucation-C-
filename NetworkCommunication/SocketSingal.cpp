#include "stdafx.h"
#include "SocketSingal.h"
#include "Common.h"
#include "NetCommuMgr.h"

namespace NetworkCommunication
{
	CSocketSingal::CSocketSingal()
	{

	}

	CSocketSingal::~CSocketSingal()
	{

	}

	void CSocketSingal::ProcessReadSingal(SOCKET socket, int type)
	{

	}

	void CSocketSingal::ProcessWriteSingal(SOCKET socket, int type)
	{

	}

	void CSocketSingal::ProcessExceptSingal(SOCKET socket, int type)
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