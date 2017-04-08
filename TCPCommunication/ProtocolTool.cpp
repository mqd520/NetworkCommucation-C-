#include "stdafx.h"
#include "ProtocolTool.h"

namespace TCPCommunication
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

	int MergeByte(BYTE fouth, BYTE trd, BYTE sec, BYTE fst)
	{
		int result = 0;
		if (fst != 0)
		{
			result += (int)(fst << 24);
		}
		if (sec != 0)
		{
			result += (int)(sec << 16);
		}
		if (trd != 0)
		{
			result += (int)(trd << 8);
		}
		if (fouth != 0)
		{
			result += (int)fouth;
		}
		return result;
	}

	int GetLenFromMultiByteBuf(BYTE* buf, int start, int end)
	{
		char* buf1 = new char[end - start];
		memcpy(buf1, buf + start, end - start);
		int len = strlen(buf1) + 1;
		delete buf1;
		return len;
	}
}
