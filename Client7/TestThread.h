#pragma once
#include "ThreadEntry.h"

using namespace NetworkCommunication;

class CTestThread : public CThreadEntry
{
protected:
	//************************************
	// Method:    线程运行事件处理
	//************************************
	void OnThreadExecute();

	//************************************
	// Method:    线程执行完毕事件处理
	//************************************
	void OnThreadCmp();

public:
	CTestThread();
	~CTestThread();
};