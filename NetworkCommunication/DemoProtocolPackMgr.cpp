#include "stdafx.h"
#include "DemoProtocol.h"
#include "StringHandle.h"

namespace NetworkCommunication
{
	BYTE* CProtocolLoginPackageMgr::Unparse(void* data, int* len)
	{
		BYTE* result = NULL;
		LPProtocolLoginPackage p = (LPProtocolLoginPackage)data;
		if (p)
		{
			int nByteLen = GetWStrByteCount(p->str);
			*len = sizeof(int) * 4 + nByteLen;
			result = new BYTE[*len];
			memcpy(result, p, sizeof(int) * 4);
			memcpy(result + sizeof(int) * 4, p->str, nByteLen);
		}
		return result;
	}

	void* CProtocolLoginPackageMgr::Parse(BYTE* buf, int len)
	{
		LPProtocolLoginPackage p = new ProtocolLoginPackage();
		memcpy(p, buf, sizeof(int) * 4);
		memcpy(p->str, buf + sizeof(int) * 4, len - sizeof(int) * 4);
		return (void*)p;
	}

	void CProtocolLoginPackageMgr::Release(void* data)
	{
		LPProtocolLoginPackage p = (LPProtocolLoginPackage)data;
		if (p)
		{
			delete p;
		}
	}
}