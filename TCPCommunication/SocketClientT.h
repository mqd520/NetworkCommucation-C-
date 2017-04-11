#pragma once

#include "SocketClient.h"

namespace TCPCommunication
{
	template<typename T>
	//socket客户端模板类
	class CSocketClientT :public CSocketClient
	{
	public:
		typedef bool(T::*LPOnRecvSocketDataT)(BYTE buf[], int len);//成员函数指针

	protected:
		T* m_pT;//调用方指针
		LPOnRecvSocketDataT m_lpfnOnRecvSocketDataT;//成员函数指针

	public:
		void SetCallbackT(LPOnRecvSocketDataT lpfnOnRecvSocketDataT, T* instance)
		{
			m_bHaslpfnRecvSocketData = true;
			m_lpfnOnRecvSocketDataT = lpfnOnRecvSocketDataT;
			m_pT = instance;
		};

		bool SendRecvData(BYTE buf[], int len)
		{
			return (m_pT->*m_lpfnOnRecvSocketDataT)(buf, len);
		};
	};
}