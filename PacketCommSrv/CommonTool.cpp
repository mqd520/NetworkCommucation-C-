#include "stdafx.h"
#include "Include/pck/CommonTool.h"
#include <objbase.h>

namespace pck
{
	CommonTool::CommonTool()
	{

	}

	string CommonTool::CreateGuid()
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

	string CommonTool::GetServerName(EServerType type)
	{
		string name = "";

		switch (type)
		{
		case pck::EServerType::Plaza:
			name = "Plaza";
			break;
		case pck::EServerType::Center:
			name = "Center";
			break;
		case pck::EServerType::None:
			name = "None";
			break;
		}

		return name;
	}
}