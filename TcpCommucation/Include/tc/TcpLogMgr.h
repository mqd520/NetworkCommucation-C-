#pragma once
#include "TcpLog.h"
#include <string>
#include <functional>

using namespace std;
using namespace std::placeholders;

namespace tc
{
	typedef std::function<void(ETcpLogType, string, void*, void*)> Fun1;

	// tcp日志管理类
	class TcpLogMgr
	{
	private:
		TcpLogMgr();

	private:
		static Fun1 fun;
		static void* pParam1;
		static void* pParam2;

	private:
		friend class TcpLog;
		//************************************
		// Method:    日志事件处理
		// Parameter: 日志类型
		// Parameter: 日志内容
		//************************************
		static void OnLog(ETcpLogType type, string log);

	public:
		//************************************
		// Method:    设置回调函数
		// Parameter: Fun1 fun
		// Parameter: 附加参数1
		// Parameter: 附加参数2
		//************************************
		static void SetCallbackFn(Fun1 fun, void* pParam1, void* pParam2);
	};
}