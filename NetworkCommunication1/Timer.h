#pragma once

namespace NetworkCommunication
{
	//定时器
	class CTimer
	{
	private:
		//************************************
		// Method:    计时完毕回调函数指针
		// FullName:  NetworkCommunication::CTimer::LPOnTimeout
		// Access:    private 
		// Returns:   是否继续计时
		// Qualifier: 
		// Parameter: * LPOnTimeout
		//************************************
		typedef bool(*LPOnTimeout)();

	protected:
		const int m_nTimeout;//超时时间
		HANDLE m_hThread;//线程句柄
		time_t m_nStartTime;//开始时间
		bool m_bRunning;//线程是否运行中
		LPOnTimeout m_lpfnOnTimeout;//超时回调函数
		bool m_bTimeout;//是否已超时

	protected:
		//************************************
		// Method:    计时完毕
		// FullName:  NetworkCommunication::CTimer::OnTimeout
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnTimeout();

	public:
		CTimer(int timeout);
		~CTimer();

		//************************************
		// Method:    计时函数(无需调用)
		// FullName:  NetworkCommunication::CTimer::Timeout
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void Timeout();

		//************************************
		// Method:    设置回调函数
		// FullName:  NetworkCommunication::CTimer::SetCallback
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: LPOnTimeout lpfnOnTimeout
		//************************************
		void SetCallback(LPOnTimeout lpfnOnTimeout);

		//************************************
		// Method:    开始计时
		// FullName:  NetworkCommunication::CTimer::Start
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void Start();

		//************************************
		// Method:    停止计时
		// FullName:  NetworkCommunication::CTimer::Stop
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void Stop();

		//************************************
		// Method:    一次超时是否已完成
		// FullName:  NetworkCommunication::CTimer::IsTimeout
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		bool IsTimeoutCmp();
	};

	//定时器(模板类)
	template<typename T>
	class CTimerT :public CTimer
	{
	private:
		//************************************
		// Method:    计时完毕回调函数指针
		// FullName:  NetworkCommunication::CTimer::LPOnTimeout
		// Access:    private 
		// Returns:   是否继续计时
		// Qualifier: 
		// Parameter: * LPOnTimeout
		//************************************
		typedef bool(T::*LPOnTimeoutT)();

	protected:
		LPOnTimeoutT m_lpfnOnTimeoutT;
		T* m_pInstance;

	public:
		CTimerT(int timeout) :CTimer(timeout)
		{
			m_lpfnOnTimeoutT = NULL;
		};
		~CTimerT(){};

		void SetCallbackT(LPOnTimeoutT lpfnOnTimeoutT, T* pInstance)
		{
			m_lpfnOnTimeoutT = lpfnOnTimeoutT;
			m_pInstance = pInstance;
		}

	protected:
		void OnTimeout()
		{
			m_bTimeout = true;
			m_bRunning = false;
			if (m_lpfnOnTimeoutT != NULL)
			{
				if ((m_pInstance->*m_lpfnOnTimeoutT)())
				{
					//继续计时
					Start();
				}
				else
				{
					::SuspendThread(m_hThread);
				}
			}
			else
			{
				::SuspendThread(m_hThread);
			}
		}
	};
}