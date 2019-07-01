#pragma once
#include "TcpLog.h"
#include <string>
#include <functional>

using namespace std;
using namespace std::placeholders;

namespace tc
{
	typedef std::function<void(ETcpLogType, string, void*, void*)> Fun1;

	// tcp��־������
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
		// Method:    ��־�¼�����
		// Parameter: ��־����
		// Parameter: ��־����
		//************************************
		static void OnLog(ETcpLogType type, string log);

	public:
		//************************************
		// Method:    ���ûص�����
		// Parameter: Fun1 fun
		// Parameter: ���Ӳ���1
		// Parameter: ���Ӳ���2
		//************************************
		static void SetCallbackFn(Fun1 fun, void* pParam1, void* pParam2);
	};
}