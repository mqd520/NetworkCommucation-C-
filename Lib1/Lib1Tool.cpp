#include "stdafx.h"
#include "Include/Lib1/Lib1Tool.h"
#include <objbase.h>

namespace lib1
{
	Lib1Tool::Lib1Tool()
	{

	}

	Lib1Tool::~Lib1Tool()
	{

	}

	string Lib1Tool::CreateGUID()
	{
		GUID guid;
		CoCreateGuid(&guid);
		static char ch[64] = { 0 };

		sprintf_s(
			ch,
			sizeof(ch),
			"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1],
			guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);

		return ch;
	}
}