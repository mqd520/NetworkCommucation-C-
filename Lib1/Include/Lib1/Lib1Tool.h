#pragma once
#include <string>

using namespace std;

namespace lib1
{
	// lib1工具类
	class Lib1Tool
	{
	public:
		Lib1Tool();
		~Lib1Tool();

		//************************************
		// Method:    生成一个GUID
		//************************************
		static string CreateGUID();
	};
}