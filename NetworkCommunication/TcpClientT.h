#pragma once

#include "TcpClient.h"
#include "StringHandle.h"

namespace NetworkCommunication
{
	template<typename T>
	//tcp模板客户端
	class CTcpClientT :public CTcpClient
	{
	public:
		//************************************
		// Method:    收到tcp数据函数指针
		// FullName:  NetworkCommunication::CTcpClientT<T>::LPOnRecvTcpDataT
		// Access:    public 
		// Returns:   指示调用者是否已释放缓冲区
		// Qualifier: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		typedef bool(T::*LPOnRecvTcpDataT)(BYTE buf[], int len);

		//************************************
		// Method:    收到tcp事件函数指针
		// FullName:  NetworkCommunication::LPOnRecvNotifyEvt
		// Access:    public 
		// Returns:   是否已处理
		// Qualifier: 事件类型
		// Parameter: 消息
		//************************************
		typedef bool(T::*LPOnRecvTcpEvtT)(TcpEvtType type, TCHAR* msg);

	protected:
		T* m_pInstanceT;//调用方实例
		LPOnRecvTcpDataT m_lpfnOnRecvTcpDataT;//接受tcp数据函数指针
		LPOnRecvTcpEvtT m_lpfnRecvTcpEvt;//接受通知函数指针

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
		// Method:    设置回调函数
		// FullName:  NetworkCommunication::CTcpClientT<T>::SetCallbackT
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 调用者实例
		// Parameter: 接收tcp数据函数指针
		// Parameter: 接收通知函数指针
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