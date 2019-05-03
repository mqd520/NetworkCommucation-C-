#pragma once
#include "Timer.h"
#include <vector>

using namespace std;

namespace tc
{
	//定时器管理
	class CTimerMgr
	{
	private:
		vector<CTimer*> m_vecTimeout;

	public:
		CTimerMgr();
		~CTimerMgr();

		//************************************
		// Method:    添加一个定时器
		// Parameter: 定时器
		//************************************
		void Add(CTimer* pTimeout);

		//************************************
		// Method:    获取定时器数目
		//************************************
		int Count();

		//************************************
		// Method:    超时事件处理
		// Parameter: 超时时间
		//************************************
		void OnTimeout(int millsecond);
	};
}