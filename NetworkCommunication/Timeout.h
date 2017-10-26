#pragma once

namespace NetworkCommunication
{
	class CTimeout;

	typedef void(*LPTimeoutCallback)(CTimeout* pTimeout, int count);

	class CTimeoutListMgr;

	//��ʱ��
	class CTimeout
	{
	private:
		int m_nTimeout;//���ʱ��(����)
		int m_nCount;//���д���,0:��������
		LPTimeoutCallback m_lpfn;//�ص�����
		bool m_bRunning;//�Ƿ���������
		int m_nTimeouted;//�Ѿ������ʱ��
		int m_nCounted;//�Ѿ����еĴ���

	private:
		friend class CTimeoutListMgr;
		void OnTimeout(int millsecond);

	public:
		CTimeout(int millsecond, LPTimeoutCallback lpfn, int count = 0);
		~CTimeout();

		void Run(bool clear = false);

		void Pause();

		bool IsRun();

		int Count();
	};
}