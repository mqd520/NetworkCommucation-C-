#pragma once
#include "tc/ThreadEntry.h"

using namespace tc;

// 日志线程类
class LogThread : public CThreadEntry
{
public:
	LogThread();
	~LogThread();

protected:
	//************************************
	// Method:    线程运行事件处理
	//************************************
	virtual void OnThreadExecute() override;
};