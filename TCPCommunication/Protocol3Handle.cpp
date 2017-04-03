#include "stdafx.h"
#include "Protocol3Handle.h"
#include "ProtocolTool.h"

using namespace ProtocolTool;

namespace Protocol3
{
	CProtocol3Handle::CProtocol3Handle()
	{

	}

	CProtocol3Handle::~CProtocol3Handle()
	{

	}

	BYTE* CProtocol3Handle::Packet(Package3Type type, BYTE buf[], int len)
	{
		BYTE* data = new BYTE[Protocol3_HeadLen + len];
		Package3Head head;
		head.highDataLen = GetTrdByteFromInt(len);
		head.lowDataLen = GetFouthByteFromInt(len);
		head.highPackageType = GetTrdByteFromInt(type);
		head.lowPackageType = GetFouthByteFromInt(type);
		memcpy(data, &head, Protocol3_HeadLen);
		memcpy(data + Protocol3_HeadLen, buf, len);
		return data;
	}

	void* CProtocol3Handle::Unpacket(BYTE buf[], int len, Package3Type type)
	{
		switch (type)
		{
		case Protocol3::type1:
			return (void*)Parse<Package31>(buf, len);
			break;
		case Protocol3::type2:
			return (void*)Parse<Package32>(buf, len);
			break;
		default:
			type = Package3Type::invalid;
			break;
		}
		return NULL;
	}

	int CProtocol3Handle::GetHeadLen()
	{
		return Protocol3_HeadLen;
	}

	int CProtocol3Handle::GetDataLen(BYTE buf[], int len)
	{
		if (len > Protocol3_HeadLen)
		{
			return MergeByte(buf[5], buf[6]);
		}
		else
		{
			return 0;
		}
	}

	Package3Type CProtocol3Handle::GetPackageType(BYTE buf[], int len)
	{
		if (len > Protocol3_HeadLen)
		{
			int type = MergeByte(buf[3], buf[4]);
			return (Package3Type)type;
		}
		else
		{
			return Package3Type::invalid;
		}
	}

	template<typename T>
	T* CProtocol3Handle::Parse(BYTE buf[], int len)
	{
		if (len > Protocol3_HeadLen)
		{
			int size = sizeof(T);
			T* p = new T[size];
			memcpy(p, buf + Protocol3_HeadLen, len - Protocol3_HeadLen);
			return p;
		}
		return NULL;
	}
}