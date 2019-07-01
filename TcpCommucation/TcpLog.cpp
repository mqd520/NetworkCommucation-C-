#include "stdafx.h"
#include "Include/tc/TcpLog.h"
#include "Include/tc/TcpLogMgr.h"

#define TCPCOM_MAXLOGLEN	(1024)		// 日志最大长度

namespace tc
{
	TcpLog::TcpLog()
	{

	}

	void TcpLog::WriteLine(ETcpLogType type /*= ETcpLogType::Info*/, string format /*= ""*/, ...)
	{
		char log[TCPCOM_MAXLOGLEN] = { 0 };
		va_list argPtr;
		va_start(argPtr, format);
		vsprintf_s(log, TCPCOM_MAXLOGLEN - 1, format.c_str(), argPtr);
		va_end(argPtr);

		TcpLogMgr::OnLog(type, log);
	}
}