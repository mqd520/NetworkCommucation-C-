#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//tcp�¼��߳�
	class CTcpEvtThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadExecute();

	public:
		CTcpEvtThread();
		~CTcpEvtThread();

		//************************************
		// Method:    ��ʼ�����߳�
		//************************************
		void Run();
	};
}