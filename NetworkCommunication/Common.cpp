#include "stdafx.h"
#include "Common.h"
#include <stdio.h>
#include <tchar.h>
#include <stdarg.h>
#pragma warning(disable:4996)

namespace NetworkCommunication
{
	void StrCopy(TCHAR* dest, TCHAR* src)
	{
#ifdef UNICODE
		wcscpy(dest, src);
#else
		
#endif // UNICODE

	}

	void Printf1(char* format, ...)
	{
		char msg1[1024] = { 0 };
		va_list  argPtr;
		va_start(argPtr, format);
		vsprintf_s(msg1, 1024 - 1, format, argPtr);
		va_end(argPtr);

		char dest[100] = { 0 };
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		sprintf(dest, "[%d-%02d-%02d %02d:%02d:%02d] %s \n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, msg1);
		printf(dest);
	}
}