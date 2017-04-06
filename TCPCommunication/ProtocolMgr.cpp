#include "stdafx.h"
#include "ProtocolMgr.h"
#include "ProtocolTool.h"

using namespace ProtocolTool;

namespace Protocol3
{
	void CProtocolMgr::Init()
	{
		m_vecParserList.push_back({ Package3Type::type1, {
			(LPPackage3Unparse)CPackage3Mgr::Package31Unparse,
			(LPPackage3Parse)CPackage3Mgr::Package31Parse,
			CPackage3Mgr::Package31Release } }
		);
		m_vecParserList.push_back({ Package3Type::type2, {
			(LPPackage3Unparse)CPackage3Mgr::CommonUnparse<Package32>,
			(LPPackage3Parse)CPackage3Mgr::CommonParse<Package32>,
			CPackage3Mgr::CommonRelease } }
		);
		m_vecParserList.push_back({ Package3Type::type3, {
			(LPPackage3Unparse)CPackage3Mgr::CommonUnparse<Package33>,
			(LPPackage3Parse)CPackage3Mgr::CommonParse<Package33>,
			CPackage3Mgr::CommonRelease } }
		);
		m_vecParserList.push_back({ Package3Type::type4, {
			(LPPackage3Unparse)CPackage3Mgr::CommonUnparse<KeepAlivePackage>,
			(LPPackage3Parse)CPackage3Mgr::CommonParse<KeepAlivePackage>,
			CPackage3Mgr::CommonRelease } }
		);
	}

	BYTE* CProtocolMgr::Packet(Package3Type type, BYTE buf[], int bodyLen, int* packetLen)
	{
		*packetLen = Protocol3_HeadLen + bodyLen;
		BYTE* data = new BYTE[*packetLen];
		Package3Head head;
		head.highDataLen = GetTrdByteFromInt(bodyLen);
		head.lowDataLen = GetFouthByteFromInt(bodyLen);
		head.highPackageType = GetTrdByteFromInt(type);
		head.lowPackageType = GetFouthByteFromInt(type);
		memcpy(data, &head, Protocol3_HeadLen);
		memcpy(data + Protocol3_HeadLen, buf, bodyLen);
		return data;
	}

	BYTE* CProtocolMgr::Packet(Package3Type type, LPPackage3Base data, int* packetLen)
	{
		ParserInfo parser = GetPacketParser(type);
		if (parser.parse)
		{
			int len = 0;
			BYTE* buf = parser.unparse(data, &len);
			if (len > 0)
			{
				BYTE* result = Packet(type, buf, len, packetLen);
				delete buf;
				return result;
			}
		}
		return NULL;
	}

	void* CProtocolMgr::Unpacket(BYTE buf[], int len)
	{
		void* p = NULL;
		if (len > Protocol3_HeadLen)
		{
			Package3Type type = GetPackageType(buf, len);
			ParserInfo parser = GetPacketParser(type);
			p = (void*)parser.parse(buf + Protocol3_HeadLen, len - Protocol3_HeadLen);
		}
		return p;
	}

	int CProtocolMgr::GetHeadLen()
	{
		return Protocol3_HeadLen;
	}

	int CProtocolMgr::GetDataLen(BYTE buf[], int len)
	{
		if (len + 1 > Protocol3_HeadLen)
		{
			return MergeByte(buf[6], buf[5]);
		}
		else
		{
			return 0;
		}
	}

	Package3Type CProtocolMgr::GetPackageType(BYTE buf[], int len)
	{
		if (len + 1 > Protocol3_HeadLen)
		{
			int type = MergeByte(buf[4], buf[3]);
			return (Package3Type)type;
		}
		else
		{
			return Package3Type::invalid;
		}
	}

	ParserInfo CProtocolMgr::GetPacketParser(Package3Type type)
	{
		ParserInfo p = { 0 };
		for (vector<Package3ParseInfo>::iterator it = m_vecParserList.begin(); it < m_vecParserList.end(); ++it)
		{
			if (it->type == type)
			{
				p = it->parser;
				break;
			}
		}
		return p;
	}

	BYTE* CProtocolMgr::GetDataBuf(BYTE* buf, int len)
	{
		int datalen = GetDataLen(buf, len);
		int headlen = GetHeadLen();
		BYTE* result = new BYTE[datalen];
		memcpy(result, buf + headlen, datalen);
		return result;
	}
}