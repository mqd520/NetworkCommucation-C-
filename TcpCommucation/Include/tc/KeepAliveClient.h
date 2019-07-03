#pragma once
#include "KeepAliveSrv.h"
#include "Timer.h"

namespace tc
{
	// �������ͻ��˷���
	class KeepAliveClient : public KeepAliveSrv
	{
	public:
		KeepAliveClient(
			int nTimespan = TC_KeepAlive_Timespan, int nTimeout = TC_KeepAlive_Timeout,
			int nMaxCount = TC_KeepAlive_MaxMissCount, void* pObj1 = NULL, void* pObj2 = NULL);
		virtual ~KeepAliveClient();

	protected:
		const int nTimespan;	// ���ͼ��ʱ��
		Timer tTimespan;				// ������������ʱ��

	protected:
		//************************************
		// Method:    ��ʱ���¼�����
		// Parameter: ��ʱ������
		// Parameter: ����
		// Parameter: void * pParam1
		// Parameter: void * pParam2
		//************************************
		void OnTimerClient(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);

		//************************************
		// Method:    �������¼�����
		//************************************
		virtual void OnKeepAlive() override;

		//************************************
		// Method:    ��ʧ�������¼�����
		// Parameter: count:	������ʧ����
		// Parameter: b:	�Ƿ��ѳ�������������
		//************************************
		virtual void OnMissKeepAlive(int count, bool b = true) override;

		//************************************
		// Method:    ��ʼ������
		//************************************
		virtual void StartKeepAlive() override;

		//************************************
		// Method:    �ر�������
		//************************************
		virtual void CloseKeepAlive() override;
	};
}