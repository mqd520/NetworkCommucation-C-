#pragma once
#include "Timer.h"
#include <vector>

using namespace std;

namespace tc
{
	//��ʱ������
	class CTimerMgr
	{
	private:
		vector<CTimer*> m_vecTimeout;

	public:
		CTimerMgr();
		~CTimerMgr();

		//************************************
		// Method:    ���һ����ʱ��
		// Parameter: ��ʱ��
		//************************************
		void Add(CTimer* pTimeout);

		//************************************
		// Method:    ��ȡ��ʱ����Ŀ
		//************************************
		int Count();

		//************************************
		// Method:    ��ʱ�¼�����
		// Parameter: ��ʱʱ��
		//************************************
		void OnTimeout(int millsecond);
	};
}