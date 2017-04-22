#pragma once

namespace NetworkCommunication
{
	//��ʱ��
	class CTimer
	{
	private:
		//************************************
		// Method:    ��ʱ��ϻص�����ָ��
		// FullName:  NetworkCommunication::CTimer::LPOnTimeout
		// Access:    private 
		// Returns:   �Ƿ������ʱ
		// Qualifier: 
		// Parameter: * LPOnTimeout
		//************************************
		typedef bool(*LPOnTimeout)();

	protected:
		const int m_nTimeout;//��ʱʱ��
		HANDLE m_hThread;//�߳̾��
		time_t m_nStartTime;//��ʼʱ��
		bool m_bRunning;//�߳��Ƿ�������
		LPOnTimeout m_lpfnOnTimeout;//��ʱ�ص�����
		bool m_bTimeout;//�Ƿ��ѳ�ʱ

	protected:
		//************************************
		// Method:    ��ʱ���
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
		// Method:    ��ʱ����(�������)
		// FullName:  NetworkCommunication::CTimer::Timeout
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void Timeout();

		//************************************
		// Method:    ���ûص�����
		// FullName:  NetworkCommunication::CTimer::SetCallback
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: LPOnTimeout lpfnOnTimeout
		//************************************
		void SetCallback(LPOnTimeout lpfnOnTimeout);

		//************************************
		// Method:    ��ʼ��ʱ
		// FullName:  NetworkCommunication::CTimer::Start
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void Start();

		//************************************
		// Method:    ֹͣ��ʱ
		// FullName:  NetworkCommunication::CTimer::Stop
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void Stop();

		//************************************
		// Method:    һ�γ�ʱ�Ƿ������
		// FullName:  NetworkCommunication::CTimer::IsTimeout
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		bool IsTimeoutCmp();
	};

	//��ʱ��(ģ����)
	template<typename T>
	class CTimerT :public CTimer
	{
	private:
		//************************************
		// Method:    ��ʱ��ϻص�����ָ��
		// FullName:  NetworkCommunication::CTimer::LPOnTimeout
		// Access:    private 
		// Returns:   �Ƿ������ʱ
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
					//������ʱ
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