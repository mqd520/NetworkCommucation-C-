#pragma once
#include "tc/ThreadEntry.h"

using namespace tc;

// ��־�߳���
class LogThread : public CThreadEntry
{
public:
	LogThread();
	~LogThread();

protected:
	//************************************
	// Method:    �߳������¼�����
	//************************************
	virtual void OnThreadExecute() override;
};