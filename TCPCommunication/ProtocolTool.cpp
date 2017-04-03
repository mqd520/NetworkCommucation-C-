#include "stdafx.h"
#include "ProtocolTool.h"

namespace ProtocolTool
{
	BYTE GetFstByteFromInt(int n)
	{
		return (BYTE)(n >> 24);
	}

	BYTE GetSecByteFromInt(int n)
	{
		return (BYTE)((n << 8) >> 24);
	}

	BYTE GetTrdByteFromInt(int n)
	{
		return (BYTE)((n << 16) >> 24);
	}

	BYTE GetFouthByteFromInt(int n)
	{
		return (BYTE)((n << 24) >> 24);
	}

	int MergeByte(BYTE high, BYTE low)
	{
		return (((int)high) << 8) + (int)low;
	}
}
