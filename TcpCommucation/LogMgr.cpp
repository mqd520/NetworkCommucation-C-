#include "stdafx.h"
#include "LogMgr.h"
#include <assert.h>

namespace tc
{
	LogMgr::LogMgr()
	{

	}

	LogMgr::~LogMgr()
	{

	}

	void LogMgr::RegCallback(LPLogCallback lpfnCallback, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		bool b = false;

		for (vector<LogCallbackInfo>::iterator it = vecCallbacks.begin(); it != vecCallbacks.end(); it++)
		{
			if (it->lpfn == lpfnCallback)
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			LogCallbackInfo info;
			info.lpfn = lpfnCallback;
			info.pParam1 = pParam1;
			info.pParam2 = pParam2;

			vecCallbacks.push_back(info);
		}
	}

	void LogMgr::RemoveCallback(LPLogCallback lpfnCallback)
	{
		for (vector<LogCallbackInfo>::iterator it = vecCallbacks.begin(); it != vecCallbacks.end(); it++)
		{
			if (it->lpfn == lpfnCallback)
			{
				vecCallbacks.erase(it);
				break;
			}
		}
	}

	void LogMgr::RemoveCallback()
	{
		vecCallbacks.clear();
	}

	void LogMgr::AddLog(int type, string format, ...)
	{
		char log[1024] = { 0 };
		va_list  argPtr;
		va_start(argPtr, format);
		vsprintf_s(log, 1024 - 1, format.c_str(), argPtr);
		va_end(argPtr);

		for (vector<LogCallbackInfo>::iterator it = vecCallbacks.begin(); it != vecCallbacks.end(); it++)
		{
			it->lpfn(type, log, it->pParam1, it->pParam2);
		}
	}
}