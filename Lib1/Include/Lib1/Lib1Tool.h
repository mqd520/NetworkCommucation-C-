#pragma once
#include <string>

using namespace std;

namespace lib1
{
	// lib1������
	class Lib1Tool
	{
	public:
		Lib1Tool();
		~Lib1Tool();

		//************************************
		// Method:    ����һ��GUID
		//************************************
		static string CreateGUID();
	};
}