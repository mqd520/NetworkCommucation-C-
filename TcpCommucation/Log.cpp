#include "stdafx.h"
#include "Include/tc/Log.h"

#define TCPCOM_MAXLOGLEN	(1024)		// max log bug len

namespace tc
{
	TcpLogCallback TcpLog::fn;


	TcpLog::TcpLog()
	{

	}

	void TcpLog::SetCallbackFn(TcpLogCallback fn)
	{
		TcpLog::fn = fn;
	}

	void TcpLog::WriteLine(ETcpLogType type, bool bOutputConsole, string format /*= ""*/, ...)
	{
		char log[TCPCOM_MAXLOGLEN] = { 0 };
		va_list argPtr;
		va_start(argPtr, format);
		vsprintf_s(log, TCPCOM_MAXLOGLEN - 1, format.c_str(), argPtr);
		va_end(argPtr);

		if (!fn._Empty())
		{
			fn(type, log, bOutputConsole);
		}
	}
}