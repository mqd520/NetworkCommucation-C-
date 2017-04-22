#pragma once

#include "TcpClient.h"
#include "StringHandle.h"

namespace NetworkCommunication
{
	template<typename T>
	//tcpģ��ͻ���
	class CTcpClientT :public CTcpClient
	{
	public:
		//************************************
		// Method:    �յ�tcp���ݺ���ָ��
		// FullName:  NetworkCommunication::CTcpClientT<T>::LPOnRecvTcpDataT
		// Access:    public 
		// Returns:   ָʾ�������Ƿ����ͷŻ�����
		// Qualifier: ������
		// Parameter: ����������
		//************************************
		typedef bool(T::*LPOnRecvTcpDataT)(BYTE buf[], int len);

		//************************************
		// Method:    �յ�tcp�¼�����ָ��
		// FullName:  NetworkCommunication::LPOnRecvNotifyEvt
		// Access:    public 
		// Returns:   �Ƿ��Ѵ���
		// Qualifier: �¼�����
		// Parameter: ��Ϣ
		//************************************
		typedef bool(T::*LPOnRecvTcpEvtT)(TcpEvtType type, TCHAR* msg);

	protected:
		T* m_pInstanceT;//���÷�ʵ��
		LPOnRecvTcpDataT m_lpfnOnRecvTcpDataT;//����tcp���ݺ���ָ��
		LPOnRecvTcpEvtT m_lpfnRecvTcpEvt;//����֪ͨ����ָ��

	protected:
		void SendTcpData(BYTE buf[], int len)
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
		};

		void SendTcpEvt(TcpEvtType type, TCHAR* msg)
		{
			if (m_lpfnRecvTcpEvt)
			{
				if (!((m_pInstanceT->*m_lpfnRecvTcpEvt)(type, msg)))
				{
					if (msg)
					{
						Printf(msg);
					}
				}
			}
		};

	public:
		//************************************
		// Method:    ���ûص�����
		// FullName:  NetworkCommunication::CTcpClientT<T>::SetCallbackT
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: ������ʵ��
		// Parameter: ����tcp���ݺ���ָ��
		// Parameter: ����֪ͨ����ָ��
		//************************************
		void SetCallbackT(T* pInstance, LPOnRecvTcpDataT lpfnOnRecvTcpDataT, LPOnRecvTcpEvtT lpfnRecvTcpEvt = NULL)
		{
			m_bHaslpfnRecvTcpData = true;
			m_pInstanceT = pInstance;
			m_lpfnOnRecvTcpDataT = lpfnOnRecvTcpDataT;
			m_lpfnRecvTcpEvt = lpfnRecvTcpEvt;
		};
	};
}