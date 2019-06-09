#pragma once
#include <vector>
#include <queue>
#include "Include/tc/Def1.h"
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// 回调函数信息
	typedef struct tagLogCallbackInfo
	{
		LPLogCallback lpfn;	// 回调函数指针
		void* pParam1;		// 附加参数1
		void* pParam2;		// 附加参数2
	}LogCallbackInfo;


	// 日志管理类
	class LogMgr
	{
	public:
		LogMgr();
		~LogMgr();

	private:
		vector<LogCallbackInfo> vecCallbacks;	// 回调函数信息集合

	public:
		//************************************
		// Method:    注册日志回调函数
		// Parameter: lpfnCallback:	回调函数指针(参看: LPLogCallback)
		// Parameter: pParam1:	附加参数1
		// Parameter: pParam2:	附加参数2
		//************************************
		void RegCallback(LPLogCallback lpfnCallback, void* pParam1 = NULL, void* pParam2 = NULL);

		//************************************
		// Method:    移除日志回调函数
		// Parameter: lpfnCallback:	回调函数指针(参看: LPLogCallback)
		//************************************
		void RemoveCallback(LPLogCallback lpfnCallback);

		//************************************
		// Method:    移除日志回调函数
		//************************************
		void RemoveCallback();

		//************************************
		// Method:    增加一条日志
		// Parameter: type:	日志类型(参看: ELogType)
		// Parameter: format:	格式化字符串
		//************************************
		void AddLog(int type, string format, ...);
	};
}