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
		buf[0] = 1;//���汾��
		buf[1] = 0;//�ΰ汾��
		buf[2] = m_nPackageHeadLen;//��ͷ����
		buf[3] = GetTrdByteFromInt(type);//������(��λ)
		buf[4] = GetFouthByteFromInt(type);//������(��λ)
		buf[5] = GetTrdByteFromInt(len);//���峤��(��λ)
		buf[6] = GetFouthByteFromInt(len);//���峤��(��λ)
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
		if (true)//������ݰ�ͷ����֤
		{
			b = true;
		}
		return true;
	}

	bool CDemoProtocolMgr::ValidatePackageType(DemoPackageType type)
	{
		bool b = false;
		if (true)//������ݰ���������֤
		{
			if (type == type1 || type == type2 || type == type3 || type == type4)
			{
				b = true;
			}
		}
		return b;
	}
}