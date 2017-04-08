#include "stdafx.h"
#include "DemoProtocolMgr.h"
#include "DemoPackageMgr.h"

using namespace ProtocolMgr;

CDemoProtocolMgr::CDemoProtocolMgr()
{
	m_nPackageHeadLen = DemoProtocol_HeadLen;
	m_nInvalidPackage = (int)DemoPackageType::invalid;
	m_nKeepAlive = (int)DemoPackageType::type4;
}

void CDemoProtocolMgr::Init()
{
	/*m_vecParserList.push_back({ DemoPackageType::type1, {
		(LPPackageUnparse)CDemoPackageMgr::DemoPackage1Unparse,
		(LPPackageParse)CDemoPackageMgr::DemoPackage1Parse,
		CDemoPackageMgr::DemoPackage1Release } }
		);*/
	CDemoProtocolMgrBase::m_vecParserList.push_back({ DemoPackageType::type1, {
		CDemoPackageMgr::DemoPackage1Unparse,
		CDemoPackageMgr::DemoPackage1Parse,
		CDemoPackageMgr::DemoPackage1Release } }
	);
}

BYTE* CDemoProtocolMgr::PacketFromBuf(DemoPackageType type, BYTE buf[], int bodyLen, int* packetLen)
{
	*packetLen = DemoProtocol_HeadLen + bodyLen;
	BYTE* data = new BYTE[*packetLen];
	DemoPackageHead head;
	head.highDataLen = GetTrdByteFromInt(bodyLen);
	head.lowDataLen = GetFouthByteFromInt(bodyLen);
	head.highPackageType = GetTrdByteFromInt(type);
	head.lowPackageType = GetFouthByteFromInt(type);
	memcpy(data, &head, DemoProtocol_HeadLen);
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