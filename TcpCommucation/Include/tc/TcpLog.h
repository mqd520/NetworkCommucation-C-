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
		static void WriteLine(ETcpLogType type = ETcpLogType::Info, string format = "", ...);
	};
}