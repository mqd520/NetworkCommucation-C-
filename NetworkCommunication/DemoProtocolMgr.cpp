#include "stdafx.h"
#include "DemoProtocolMgr.h"
#include "ProtocolTool.h"
#include "DemoPackageMgr.h"

namespace NetworkCommunication
{
#define DemoProtocol_HeadLen	7	//Э��ͷ����

	CDemoProtocolMgr::CDemoProtocolMgr()
	{
		m_nPackageHeadLen = DemoProtocol_HeadLen;
		m_nInvalidPackage = (int)DemoPackageType::invalid;
		m_nKeepAlive = (int)DemoPackageType::type4;
	}

	void CDemoProtocolMgr::AssoicatePackageType()
	{
		m_vecPackageMgr.push_back({ DemoPackageType::type1, new CDemoPackage1Mgr() });
		m_vecPackageMgr.push_back({ DemoPackageType::type2, new CDemoPackageMgr<DemoPackage2>() });
		m_vecPackageMgr.push_back({ DemoPackageType::type3, new CDemoPackageMgr<DemoPackage3>() });
	}

	void CDemoProtocolMgr::InitPackageHeadBuf(DemoPackageType type, int len)
	{
		m_pPackageHeadBuf[0] = 1;//���汾��
		m_pPackageHeadBuf[1] = 0;//�ΰ汾��
		m_pPackageHeadBuf[2] = DemoProtocol_HeadLen;//��ͷ����
		m_pPackageHeadBuf[3] = GetTrdByteFromInt(type);//������(��λ)
		m_pPackageHeadBuf[4] = GetFouthByteFromInt(type);//������(��λ)
		m_pPackageHeadBuf[5] = GetTrdByteFromInt(len);//���峤��(��λ)
		m_pPackageHeadBuf[6] = GetFouthByteFromInt(len);//���峤��(��λ)
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