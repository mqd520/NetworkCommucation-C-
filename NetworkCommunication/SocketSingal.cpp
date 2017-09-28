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

			if (data.singaltype == SocketSingalType::Read)//处理可读信号
			{
				ProcessReadSingal(data.socket, data.sockettype);
			}
			else if (data.singaltype == SocketSingalType::Write)//处理可写信号
			{
				ProcessWriteSingal(data.socket, data.sockettype);
			}
			else if (data.singaltype == SocketSingalType::Except)//处理异常信号
			{
				ProcessExceptSingal(data.socket, data.sockettype);
			}

			//通知select层当前socket当前信号已处理完毕
			CNetworkCommuMgr::GetSelect()->OnProcessingSocketCmp(data.socket, data.singaltype);
		}
	}
}