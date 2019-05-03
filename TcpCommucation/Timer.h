#pragma once

namespace tc
{
	class CTimer;

	typedef void(*LPTimeoutCallback)(CTimer* pTimeout, int count);

	class CTimerMgr;

	//��ʱ��
	class CTimer
	{
	private:
		int m_nTimeout;//���ʱ��(����)
		int m_nCount;//���д���,0:��������
		LPTimeoutCallback m_lpfn;//�ص�����
		bool m_bRunning;//�Ƿ���������
		int m_nTimeouted;//�Ѿ������ʱ��
		int m_nCounted;//�Ѿ����еĴ���

	private:
		friend class CTimerMgr;
		void OnTimeout(int millsecond);

	public:
		CTimer(int millsecond, LPTimeoutCallback lpfn, int count = 0);
		~CTimer();

		//************************************
		// Method:    ��ʼ���ж�ʱ��
		// Parameter: �Ƿ�������ۼƵĳ�ʱʱ��
		//************************************
		void Run(bool clear = false);

		//************************************
		// Method:    ��ͣ��ʱ
		//************************************
		void Pause();

		//************************************
		// Method:    �Ƿ�������
		//************************************
		bool IsRun();

		//************************************
		// Method:    ��ȡ���д���
		//************************************
		int Count();
	};
}