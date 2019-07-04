#include "stdafx.h"
#include "ExceptionHandler.h"
#include <windows.h>
#include <DbgHelp.h>

typedef BOOL(WINAPI * MiniDumpWriteDumpT)(
	HANDLE,
	DWORD,
	HANDLE,
	MINIDUMP_TYPE,
	PMINIDUMP_EXCEPTION_INFORMATION,
	PMINIDUMP_USER_STREAM_INFORMATION,
	PMINIDUMP_CALLBACK_INFORMATION
	);

LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo);
int GenerateMiniDump(PEXCEPTION_POINTERS pExceptionPointers);

LPExceptionCallback _lpfnCallback = NULL;	// 回调函数指针
void*				_pParam1 = NULL;		// 附加参数1
void*				_pParam2 = NULL;		// 附加参数2
string				_strFilename = "";		// 文件名

ExceptionHandler::ExceptionHandler()
{

}

ExceptionHandler::~ExceptionHandler()
{

}

void ExceptionHandler::Init()
{
	SetUnhandledExceptionFilter(ExceptionFilter);
}

void ExceptionHandler::RegExceptionCallback(LPExceptionCallback lpfnCallback, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
{
	_lpfnCallback = lpfnCallback;
	_pParam1 = pParam1;
	_pParam1 = pParam2;
}

void ExceptionHandler::SetFileName(string strFilename)
{
	_strFilename = strFilename;
}

LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
{
	if (IsDebuggerPresent())
	{
		return EXCEPTION_CONTINUE_SEARCH;
	}
	int ret = GenerateMiniDump(lpExceptionInfo);

	if (_lpfnCallback != NULL)
	{
		_lpfnCallback(_pParam1, _pParam2);
	}

	return ret;
}

int GenerateMiniDump(PEXCEPTION_POINTERS pExceptionPointers)
{
	MiniDumpWriteDumpT pfnMiniDumpWriteDump = NULL;
	HMODULE hDbgHelp = LoadLibrary(_T("DbgHelp.dll"));
	if (NULL == hDbgHelp)
	{
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	pfnMiniDumpWriteDump = (MiniDumpWriteDumpT)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");

	if (NULL == pfnMiniDumpWriteDump)
	{
		FreeLibrary(hDbgHelp);
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	char szFileName[MAX_PATH] = { 0 };
	SYSTEMTIME stLocalTime;
	GetLocalTime(&stLocalTime);
	sprintf_s(szFileName, "%s_%04d-%02d-%02d_%02d-%02d-%02d.dmp",
		_strFilename.c_str(), stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
		stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond);
	HANDLE hDumpFile = CreateFileA(szFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);

	if (INVALID_HANDLE_VALUE == hDumpFile)
	{
		FreeLibrary(hDbgHelp);
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	MINIDUMP_EXCEPTION_INFORMATION expParam;
	expParam.ThreadId = GetCurrentThreadId();
	expParam.ExceptionPointers = pExceptionPointers;
	expParam.ClientPointers = FALSE;
	pfnMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
		hDumpFile, MiniDumpWithDataSegs, (pExceptionPointers ? &expParam : NULL), NULL, NULL);

	CloseHandle(hDumpFile);
	FreeLibrary(hDbgHelp);

	return EXCEPTION_EXECUTE_HANDLER;
}