#pragma once
#include "Def.h"

#include <string>
using namespace std;

namespace tc
{
	// TcpLog Callback fn
	// ETcpLogType:		Tcp Log Type
	// string:			Log
	// bool:			whether output to console
	typedef std::function<void(ETcpLogType, string, bool)> TcpLogCallback;


	// log srv
	class TcpLog final
	{
	private:
		TcpLog();

	private:
		static TcpLogCallback fn;		// Tcp Log Callback fn

	public:
		//************************************
		// Method:    Set callback fn
		// Parameter: TcpLogCallback fn
		//************************************
		static void SetCallbackFn(TcpLogCallback fn);

		//************************************
		// Method:    WriteLine
		// Parameter: ETcpLogType type
		// Parameter: bool bOutputConsole:	whether output to console
		// Parameter: string format
		// Parameter: ...
		//************************************
		static void WriteLine(ETcpLogType type, bool bOutputConsole, string format = "", ...);
	};
}