#pragma once

#include "TcpClient.h"

namespace NetworkCommunication
{
	template<typename T>
	//tcp模板客户端
	class CTcpClientT :public CTcpClient
	{
	public:
		//************************************
		// Method:    成员函数指针
		// FullName:  NetworkCommunication::CTcpClientT<T>::LPOnRecvTcpDataT
		// Access:    public 
		// Returns:   指示调用者是否已释放缓冲区
		// Qualifier: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		typedef bool(T::*LPOnRecvTcpDataT)(BYTE buf[], int len);

	protected:
		T* m_pInstanceT;//调用方实例
		LPOnRecvTcpDataT m_lpfnOnRecvTcpDataT;//成员函数指针

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