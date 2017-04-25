#include "stdafx.h"
#include "DemoProtocol.h"
#include "ByteStream.h"

namespace NetworkCommunication
{
	BYTE* CProtocolLoginPackageMgr::Unparse(void* data, int* len)
	{
		BYTE* buf = NULL;
		LPProtocolLoginPackage p = (LPProtocolLoginPackage)data;
		if (p)
		{
			CByteStream s(100);
			s.WriteByte(p->cbCurrentServerType);
			s.WriteByte(p->cbRequestServerID);
			s.WriteByte(p->cbKeepAlive);
			s.WriteInt(p->nVersion);
			s.WriteInt((int)strlen(p->strGuid) + 1);
			s.Write((BYTE*)p->strGuid, (int)strlen(p->strGuid) + 1);
			buf = new BYTE[s.GetDataLen()];
			memcpy(buf, s.GetBuf(), s.GetDataLen());
			if (len != NULL)
			{
				*len = s.GetDataLen();
			}
		}
		return buf;
	}

	void* CProtocolLoginPackageMgr::Parse(BYTE* buf, int len)
	{
		LPProtocolLoginPackage p = new ProtocolLoginPackage();
		//memcpy(p, buf, sizeof(int) * 4);
		//memcpy(p->str, buf + sizeof(int) * 4, len - sizeof(int) * 4);
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