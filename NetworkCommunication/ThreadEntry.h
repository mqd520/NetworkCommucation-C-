#pragma once

namespace NetworkCommunication
{
	class CThread;

	//�߳������
	class CThreadEntry
	{
	protected:
		CThread* m_pThread;//�̶߳���

	protected:
		friend class CThread;
		//************************************
		// Method:    �߳������¼�����
		//************************************
		virtual void OnThreadRun();

	public:
		CThreadEntry();
		~CThreadEntry();

		//************************************
		// Method:    ��ʼ�����߳�
		//************************************
		virtual void Run();
	};
}