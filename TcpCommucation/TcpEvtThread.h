#pragma once
#include "Include/tc/ThreadEntry.h"

namespace tc
{
	//tcp�¼��߳�
	class TcpEvtThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadExecute();

	public:
		TcpEvtThread();
		~TcpEvtThread();

		//************************************
		// Method:    ��ʼ�����߳�
		//************************************
		void Run();
	};
}