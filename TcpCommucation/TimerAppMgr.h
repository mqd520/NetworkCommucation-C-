#pragma once
#include "BuildTimeoutThread.h"
#include "ProcessTimeoutThread.h"
#include "TimeoutMgr.h"
#include "TimerMgr.h"

namespace NetworkCommunication
{
	//��ʱ��Ӧ�ù���
	class CTimerAppMgr
	{
	private:
		static bool m_bExit;//�Ƿ���Ҫ�˳�
		static int m_nTimeoutUnit;//��ʱ��λ
		static CProcessTimeoutThread m_processTimeoutThread;//����ʱ�߳�
		static CBuildTimeoutThread m_buildTimeoutThread;//���ɳ�ʱ�߳�
		static CTimerMgr m_timerMgr;//��ʱ������
		static CTimeoutMgr m_timeoutMgr;//��ʱ����

	public:
		CTimerAppMgr();
		~CTimerAppMgr();

		//************************************
		// Method:    ��ʼ��
		//************************************
		static void Init();

		//************************************
		// Method:    �˳�
		//************************************
		static void Exit();

		//************************************
		// Method:    ��ȡ��ʱ��λʱ��
		//************************************
		static int GetTimeoutUnit();

		//************************************
		// Method:    ���ó�ʱ��λʱ��
		// Parameter: ��ʱʱ��
		//************************************
		static void SetTimeoutUnit(int millsecond);

		//************************************
		// Method:    ��ȡ�û��Ƿ�ָʾ��Ҫ�˳�
		//************************************
		static bool CanExit();

		//************************************
		// Method:    ��ȡ��ʱ������
		//************************************
		static CTimerMgr* GetTimerMgr();

		//************************************
		// Method:    ��ȡ��ʱ����
		//************************************
		static CTimeoutMgr* GetTimeoutMgr();
	};
}