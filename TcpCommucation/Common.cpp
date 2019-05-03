#include "stdafx.h"
#include "Common.h"
#include <stdio.h>
#include <tchar.h>
#include <stdarg.h>
#pragma warning(disable:4996)

namespace tc
{
	void MyPrintf(int type, TCHAR* format, ...)
	{
		//取出可变参数
		TCHAR msg1[PRINTFMAXLEN] = { 0 };
		va_list  argPtr;
		va_start(argPtr, format);
#ifdef _UNICODE
		vswprintf_s(msg1, 1024 - 1, format, argPtr);
#else
		vsprintf_s(msg1, 1024 - 1, format, argPtr);
#endif // _UNICODE
		va_end(argPtr);

		//增加时间头
		TCHAR dest[PRINTFMAXLEN] = { 0 };
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		wsprintf(dest, L"[%d-%02d-%02d %02d:%02d:%02d] %s \n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, msg1);
		dest[PRINTFMAXLEN - 1] = 0;

		//设置颜色
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

		_tprintf(dest);
	}
}