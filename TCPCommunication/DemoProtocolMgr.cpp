#include "stdafx.h"
#include "DemoProtocolMgr.h"
#include "DemoPackageMgr.h"

namespace TCPCommunication
{
#define DemoProtocol_HeadLen	7	//Э��ͷ����

	CDemoProtocolMgr::CDemoProtocolMgr()
	{
		m_nPackageHeadLen = DemoProtocol_HeadLen;
		m_nInvalidPackage = (int)DemoPackageType::invalid;
		m_nKeepAlive = (int)DemoPackageType::type4;
	}

	void CDemoProtocolMgr::Init()
	{
		m_vecPackageMgr.push_back({ DemoPackageType::type1, new CDemoPackage1Mgr() });
		m_vecPackageMgr.push_back({ DemoPackageType::type2, new CDemoPackageMgr<DemoPackage1>() });
		m_vecPackageMgr.push_back({ DemoPackageType::type3, new CDemoPackageMgr<DemoPackage1>() });
	}

	BYTE* CDemoProtocolMgr::PacketFromBuf(DemoPackageType type, BYTE buf[], int bodyLen, int* packetLen)
	{
		*packetLen = DemoProtocol_HeadLen + bodyLen;
		BYTE* data = new BYTE[*packetLen];
		data[0] = 1;//���汾��
		data[1] = 0;//�ΰ汾��
		data[2] = DemoProtocol_HeadLen;//��ͷ����
		data[3] = GetTrdByteFromInt(bodyLen);//������(��λ)
		data[4] = GetFouthByteFromInt(bodyLen);//������(��λ)
		data[5] = GetTrdByteFromInt(type);//���峤��(��λ)
		data[6] = GetFouthByteFromInt(type);//���峤��(��λ)
		memcpy(data + DemoProtocol_HeadLen, buf, bodyLen);
		return data;
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