#pragma once
#include "Def.h"
#include <string>
using namespace std;

namespace pck
{
	// pck srv tool
	class CommonTool final
	{
	private:
		CommonTool();

	public:
		//************************************
		// Method:    创建一个guid
		//************************************
		static string CreateGuid();

		//************************************
		// Method:    获取服务器名字
		// Parameter: EServerType type
		//************************************
		static string GetServerName(EServerType type);
	};
}