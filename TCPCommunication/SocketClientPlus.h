#pragma once

#include "SocketClient.h"

namespace TCPCommunication
{
	template<typename T>
	class CSocketClientPlus :public CSocketClient
	{
	public:
		typedef void(T::*LPOnMemRecvSocketData)(BYTE buf[], int len);//��Ա����ָ��

	protected:
		T* m_pT;//���÷�ָ��
		LPOnMemRecvSocketData m_lpfn;//��Ա����ָ��

	public:
		void Init(const TCHAR* ip, int port, LPOnMemRecvSocketData lpfn = NULL, T* p = NULL)
		{
			m_pT = p;
			m_lpfn = lpfn;
			m_bInited = true;
			m_strServerIP = ip;
			m_nServerPort = port;
		};

		void OnRecvData(BYTE buf[], int len)
		{
			if (m_lpfn&&m_pT)
			{
				try
				{
					(m_pT->*m_lpfn)(buf, len);
				}
				catch (int)
				{

				}
			}
		};
	};
}