#pragma once
#include "Def.h"
using namespace std;

namespace tc
{
	// log srv
	class TcpLog
	{
	private:
		TcpLog();

	public:
		//************************************
		// Method:    д��һ����־
		// Parameter: ETcpLogType type
		// Parameter: string format
		// Parameter: ...
		//************************************
		static void WriteLine(ETcpLogType type = ETcpLogType::Info, string format = "", ...);
	};
}