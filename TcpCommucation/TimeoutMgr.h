#pragma once
#include <queue>
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	//��ʱ�¼�����
	class CTimeoutMgr
	{
	private:
		queue<int> m_quTimeout;//��ʱ����
		CThreadLock m_lock1;//�߳���,���m_vecTimeout����

	public:
		CTimeoutMgr();
		~CTimeoutMgr();

		//************************************
		// Method:    ���һ����ʱ����
		// Parameter: ��ʱʱ��
		//************************************
		void Add(int millsecond);

		//************************************
		// Method:    ����ʱ����
		//************************************
		void ProcessTimeout();
	};
}