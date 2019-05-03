#pragma once
#pragma warning(disable:4996)

#include <string>
#include <WinSock2.h>

using namespace std;

namespace tc
{
	//线程信息
	typedef struct tagThreadInfo
	{
		HANDLE hThread;//线程句柄
		DWORD dwThreadID;//线程ID
		bool bPause;//线程状态(暂停与否)
	}ThreadInfo, *LPThreadInfo;

	//************************************
	// Method:    打印信息
	// FullName:  NetworkCommunication::Printf
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: TCHAR * msg
	//************************************
	void Printf(TCHAR* msg);

	//************************************
	// Method:    获取本地IP
	// FullName:  NetworkCommunication::GetLocalIP
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: TCHAR * ip
	//************************************
	bool GetLocalIP(TCHAR* ip);

	void PauseThread(ThreadInfo* info, bool pause);
}
