#pragma once
#include "Thread.h"
#include <vector>

using namespace std;

namespace tc
{
	class CThreadMgr
	{
	private:
		vector<CThread*> m_vecThread;

	public:
		CThreadMgr();
		~CThreadMgr();

		void AddRecycleThread(CThread* pThread);
		void Recycle();
	};
}