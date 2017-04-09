#include "stdafx.h"
#include "DemoProtocolMgr.h"
#include "DemoPackageMgr.h"
#include "ProtocolTool.h"

namespace TCPCommunication
{
#define DemoProtocol_HeadLen	7	//协议头长度

	CDemoProtocolMgr::CDemoProtocolMgr()
	{
		m_nPackageHeadLen = DemoProtocol_HeadLen;
		m_nInvalidPackage = (int)DemoPackageType::invalid;
		m_nKeepAlive = (int)DemoPackageType::type4;
	}

	void CDemoProtocolMgr::Init()
	{
		m_vecPackageMgr.push_back({ DemoPackageType::type1, new CDemoPackage1Mgr() });
		m_vecPackageMgr.push_back({ DemoPackageType::type2, new CDemoPackageMgr<DemoPackage2>() });
		m_vecPackageMgr.push_back({ DemoPackageType::type3, new CDemoPackageMgr<DemoPackage3>() });
	}

	BYTE* CDemoProtocolMgr::PacketFromBuf(DemoPackageType type, BYTE buf[], int bufLen, int* packetLen)
	{
		*packetLen = DemoProtocol_HeadLen + bufLen;
		BYTE* data = new BYTE[*packetLen];
		data[0] = 1;//主版本号
		data[1] = 0;//次版本号
		data[2] = DemoProtocol_HeadLen;//包头长度
		data[3] = GetTrdByteFromInt(type);//包类型(高位)
		data[4] = GetFouthByteFromInt(type);//包类型(低位)
		data[5] = GetTrdByteFromInt(bufLen);//包体长度(高位)
		data[6] = GetFouthByteFromInt(bufLen);//包体长度(低位)
		memcpy(data + DemoProtocol_HeadLen, buf, bufLen);
		return data;
	}

	int CDemoProtocolMgr::GetDataLen(BYTE buf[], int len)
	{
		if (len + 1 > m_nPackageHeadLen)
		{
			return MergeByte(buf[6], buf[5]);
		}
		else
		{
			return 0;
		}
	}

	DemoPackageType CDemoProtocolMgr::GetPackageType(BYTE buf[], int len)
	{
		if (len + 1 > m_nPackageHeadLen)
		{
			int type = MergeByte(buf[4], buf[3]);
			return DemoPackageType(type);
		}
		else
		{
			return DemoPackageType(m_nPackageHeadLen);
		}
	}

	bool CDemoProtocolMgr::ValidateKeepAlivePackage(DemoPackageBase* data)
	{
		LPKeepAlivePackage p = (LPKeepAlivePackage)data;
		if (p)
		{
			return p->n == 0 ? true : false;
		}
		return false;
	}
}