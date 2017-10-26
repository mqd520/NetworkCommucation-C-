#pragma once
#include "Timeout.h"
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	//��ʱ���б����
	class CTimeoutListMgr
	{
	private:
		vector<CTimeout*> m_vecTimeout;

	public:
		CTimeoutListMgr();
		~CTimeoutListMgr();

		void Add(CTimeout* pTimeout);

		int Count();

		void OnTimeout(int millsecond);
	};
}