#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//select�߳�
	class CSelectThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadRun();

	public:
		CSelectThread();
		~CSelectThread();
	};
}