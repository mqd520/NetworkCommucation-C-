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

		//************************************
		// Method:    �յ�tcp�ͻ����¼�����ָ��
		// FullName:  NetworkCommunication::LPOnRecvNotifyEvt
		// Access:    public 
		// Returns:   �Ƿ��Ѵ���
		// Qualifier: �¼�����
		// Parameter: ��Ϣ
		//************************************
		typedef bool(T::*LPOnRecvNotifyEvtT)(TcpClientEvtType type, TCHAR* msg);

	protected:
		T* m_pInstanceT;//���÷�ʵ��
		LPOnRecvTcpDataT m_lpfnOnRecvTcpDataT;//����tcp���ݺ���ָ��
		LPOnRecvNotifyEvtT m_lpfnRecvNotify;//����֪ͨ����ָ��

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
		void SetCallbackT(T* pInstance, LPOnRecvTcpDataT lpfnOnRecvTcpDataT, LPOnRecvNotifyEvtT lpfnRecvNotify = NULL)
		{
			m_bHaslpfnRecvTcpData = true;
			m_pInstanceT = pInstance;
			m_lpfnOnRecvTcpDataT = lpfnOnRecvTcpDataT;
			m_lpfnRecvNotify = lpfnRecvNotify;
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

		void SendNotifyEvt(TcpClientEvtType type, TCHAR* msg)
		{
			if (m_lpfnRecvNotify)
			{
				if (!((m_pInstanceT->*m_lpfnRecvNotify)(type, msg)))
				{
					if (type == error || type == Debug || type == TcpClientEvtType::Info)
					{
						Printf(msg);
					}
				}
			}
		}
	};
}