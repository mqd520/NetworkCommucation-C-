#include "stdafx.h"
#include "Common.h"
#include <stdio.h>
#include <tchar.h>
#include <stdarg.h>
#pragma warning(disable:4996)

namespace NetworkCommunication
{
	void MyPrintf(int type, char* format, ...)
	{
		char msg1[PRINTFMAXLEN] = { 0 };
		va_list  argPtr;
		va_start(argPtr, format);
		vsprintf_s(msg1, 1024 - 1, format, argPtr);
		va_end(argPtr);

		char dest[PRINTFMAXLEN] = { 0 };
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		sprintf(dest, "[%d-%02d-%02d %02d:%02d:%02d] %s \n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, msg1);
		dest[PRINTFMAXLEN - 1] = 0;

		WORD color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		switch (type)
		{
		case EInfoType::Info:
			break;
		case EInfoType::Debug:
			color = FOREGROUND_BLUE | FOREGROUND_GREEN;
			break;
		case EInfoType::Error:
			color = FOREGROUND_RED;
			break;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		printf(dest);
	}
}