#pragma once
#include "ThreadEntry.h"

namespace tc
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