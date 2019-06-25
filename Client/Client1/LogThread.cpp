#include "stdafx.h"
#include "LogThread.h"
#include "LogSrv.h"

LogThread::LogThread()
{

}

LogThread::~LogThread()
{

}

void LogThread::OnThreadExecute()
{
	if (LogSrv::GetInstance()->IsEmpty())
	{
		SetSleepTime(10);
	}
	else
	{
		LogSrv::GetInstance()->ProcessLog();
	}
}