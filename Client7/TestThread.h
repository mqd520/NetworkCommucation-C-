#pragma once
#include "ThreadEntry.h"

using namespace NetworkCommunication;

class CTestThread : public CThreadEntry
{
protected:
	//************************************
	// Method:    �߳������¼�����
	//************************************
	void OnThreadExecute();

	//************************************
	// Method:    �߳�ִ������¼�����
	//************************************
	void OnThreadCmp();

public:
	CTestThread();
	~CTestThread();
};