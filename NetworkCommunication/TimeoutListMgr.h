#pragma once
#include "Timeout.h"
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	//超时器列表管理
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