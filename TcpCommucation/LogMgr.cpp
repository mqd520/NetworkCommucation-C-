#include "stdafx.h"
#include "LogMgr.h"

namespace tc
{
	LogMgr::LogMgr()
	{

	}

	LogMgr::~LogMgr()
	{

	}

	void LogMgr::RegCallback(LPLogCallback lpfnCallback, void* pParam1, void* pParam2)
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
		lock1.Lock();

		char log[1024] = { 0 };
		va_list  argPtr;
		va_start(argPtr, format);
		vsprintf_s(log, 1024 - 1, format.c_str(), argPtr);
		va_end(argPtr);

		string strLogType = "";
		switch (type)
		{
		case ELogType::Info:
			strLogType = "Info";
			break;
		case ELogType::Debug:
			strLogType = "Debug";
			break;
		case ELogType::Err:
			strLogType = "Err";
			break;
		}

		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		char ch[1024] = { 0 };
		sprintf_s(ch, "[%s] [%d-%02d-%02d %02d:%02d:%02d] %s \n", strLogType.c_str(), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, log);

		LogInfo info = { type, ch };
		quLogs.push(info);

		lock1.Unlock();
	}

	void LogMgr::ProcessLog()
	{
		lock1.Lock();

		while (!quLogs.empty())
		{
			LogInfo info = quLogs.front();
			quLogs.pop();

			for (vector<LogCallbackInfo>::iterator it = vecCallbacks.begin(); it != vecCallbacks.end(); it++)
			{
				it->lpfn(info.type, info.log, it->pParam1, it->pParam2);
			}
		}

		lock1.Unlock();
	}

	bool LogMgr::IsEmpty()
	{
		lock1.Lock();

		bool b = quLogs.empty();

		lock1.Unlock();

		return b;
	}
}