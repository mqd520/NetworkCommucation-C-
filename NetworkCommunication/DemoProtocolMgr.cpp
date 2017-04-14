#include "stdafx.h"
#include "DemoProtocolMgr.h"
#include "ProtocolTool.h"
#include "DemoPackageMgr.h"

namespace NetworkCommunication
{
#define DemoProtocol_HeadLen	7	//协议头长度

	CDemoProtocolMgr::CDemoProtocolMgr()
	{
		m_nPackageHeadLen = DemoProtocol_HeadLen;
		m_nKeepAlive = (int)DemoPackageType::type4;
	}

	void CDemoProtocolMgr::AssoicatePackageType()
	{
		m_vecPackageMgr.push_back({ DemoPackageType::type1, new CDemoPackage1Mgr() });
		m_vecPackageMgr.push_back({ DemoPackageType::type2, new CDemoPackageMgr<DemoPackage2>() });
		m_vecPackageMgr.push_back({ DemoPackageType::type3, new CDemoPackageMgr<DemoPackage3>() });
	}

	BYTE* CDemoProtocolMgr::GetPackageHeadBuf(DemoPackageType type, int len)
	{
		BYTE* buf = new BYTE[m_nPackageHeadLen];
		buf[0] = 1;//主版本号
		buf[1] = 0;//次版本号
		buf[2] = m_nPackageHeadLen;//包头长度
		buf[3] = GetTrdByteFromInt(type);//包类型(高位)
		buf[4] = GetFouthByteFromInt(type);//包类型(低位)
		buf[5] = GetTrdByteFromInt(len);//包体长度(高位)
		buf[6] = GetFouthByteFromInt(len);//包体长度(低位)
		return buf;
	}

	int CDemoProtocolMgr::GetDataLen(BYTE buf[], int len)
	{
		if (len >= m_nPackageHeadLen)
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
		if (len >= m_nPackageHeadLen)
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

	bool CDemoProtocolMgr::ValidatePackageHead(BYTE buf[])
	{
		bool b = false;
		if (true)//具体根据包头来验证
		{
			b = true;
		}
		return true;
	}

	bool CDemoProtocolMgr::ValidatePackageType(DemoPackageType type)
	{
		bool b = false;
		if (true)//具体根据包类型来验证
		{
			if (type == type1 || type == type2 || type == type3 || type == type4)
			{
				b = true;
			}
		}
		return b;
	}
}