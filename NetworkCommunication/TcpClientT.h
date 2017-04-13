#pragma once

#include "TcpClient.h"

namespace NetworkCommunication
{
	template<typename T>
	//tcpģ��ͻ���
	class CTcpClientT :public CTcpClient
	{
	public:
		//************************************
		// Method:    ��Ա����ָ��
		// FullName:  NetworkCommunication::CTcpClientT<T>::LPOnRecvTcpDataT
		// Access:    public 
		// Returns:   ָʾ�������Ƿ����ͷŻ�����
		// Qualifier: ������
		// Parameter: ����������
		//************************************
		typedef bool(T::*LPOnRecvTcpDataT)(BYTE buf[], int len);

	protected:
		T* m_pInstanceT;//���÷�ʵ��
		LPOnRecvTcpDataT m_lpfnOnRecvTcpDataT;//��Ա����ָ��

	public:
		void SetCallbackT(LPOnRecvTcpDataT lpfnOnRecvTcpDataT, T* pInstance)
		{
			m_bHaslpfnRecvTcpData = true;
			m_lpfnOnRecvTcpDataT = lpfnOnRecvTcpDataT;
			m_pInstanceT = pInstance;
		};

		void OnRecvTcpData(BYTE buf[], int len)
		{
			if (m_lpfnOnRecvTcpDataT&&buf&&len > 0)
			{
				if (!(m_pInstanceT->*m_lpfnOnRecvTcpDataT)(buf, len))
				{
					delete buf;
				}
			}
			else
			{
				delete buf;
			}
		}
	};
}