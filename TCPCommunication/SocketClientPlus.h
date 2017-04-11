#pragma once

#include "SocketClient.h"

namespace TCPCommunication
{
	template<typename T>
	//socket客户端模板类
	class CSocketClientT :public CSocketClient
	{
	public:
		typedef void(T::*LPOnRecvSocketDataT)(BYTE buf[], int len);//成员函数指针

	protected:
		T* m_pT;//调用方指针
		LPOnRecvSocketDataT m_lpfnOnRecvSocketDataT;//成员函数指针

	public:
		void SetCallback(LPOnRecvSocketDataT lpfnOnRecvSocketDataT)
		{
			m_lpfnOnRecvSocketDataT = lpfnOnRecvSocketDataT;
		};

		void CSocketClient::ReadCatchSocketData()
		{
			if (m_vecCatchRecvSocketBuf.size() > 0)
			{
				BYTE* buf = (BYTE*)(m_vecCatchRecvSocketBuf[0].adress);
				int len = m_vecCatchRecvSocketBuf[0].len;
				m_vecCatchRecvSocketBuf.erase(m_vecCatchRecvSocketBuf.begin());
				if (m_lpfnOnRecvSocketDataT && buf)
				{
					m_lpfnPlusOnRecvSocketData(buf, len);
					delete buf;
				}
			}
		}
	};
}