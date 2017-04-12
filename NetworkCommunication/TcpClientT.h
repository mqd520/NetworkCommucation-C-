#pragma once

#include "TcpClient.h"

namespace NetworkCommunication
{
	template<typename T>
	//tcpģ��ͻ���
	class CTcpClientT :public CTcpClient
	{
	public:
		typedef bool(T::*LPOnRecvSocketDataT)(BYTE buf[], int len);//��Ա����ָ��

	protected:
		T* m_pT;//���÷�ָ��
		LPOnRecvSocketDataT m_lpfnOnRecvSocketDataT;//��Ա����ָ��

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