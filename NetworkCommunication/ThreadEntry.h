#pragma once

namespace NetworkCommunication
{
	//�߳������
	class CThreadEntry
	{
	public:
		CThreadEntry();
		~CThreadEntry();

		//************************************
		// Method:    �߳������¼�����
		//************************************
		virtual void OnThreadRun();
	};
}