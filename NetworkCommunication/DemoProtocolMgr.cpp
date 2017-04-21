#include "stdafx.h"
#include "DemoProtocolMgr.h"
#include "ProtocolTool.h"
#include "NetTool.h"

namespace NetworkCommunication
{
#define DemoProtocol_HeadLen	7	//协议头长度

	CDemoProtocolMgr::CDemoProtocolMgr()
	{
		//必需
		m_nPackageHeadLen = DemoProtocol_HeadLen;//指定包头长度

		// 非必需
		m_nKeepAlive = DemoPackageType::KeepAlive;//指定心跳包类型(非-999)
		m_pKeepAlive = new KeepAlivePackage();//指定心跳包
		m_nKeepAliveFailMaxCount = 3;//指定心跳包允许失败最大值
		m_nKeepAliveTimespan = 2 * 1000;//指定心跳包间隔时间
	}

	void CDemoProtocolMgr::AssociatePackageType()
	{
		m_vecPackageMgr.push_back({ DemoPackageType::Login, new CCommonPackageMgr<LoginPackage>() });
		m_vecPackageMgr.push_back({ DemoPackageType::LoginReply, new CCommonPackageMgr<LoginReplyPackage>() });
		m_vecPackageMgr.push_back({ DemoPackageType::KeepAlive, new CCommonPackageMgr<KeepAlivePackage>() });
	}

	BYTE* CDemoProtocolMgr::GetPackageHeadBuf(int type, int len)
	{
		BYTE* buf = new BYTE[m_nPackageHeadLen];
		buf[0] = 127;//主版本号
		buf[1] = 104;//次版本号
		buf[2] = GetTrdByteFromInt(type);//包类型(高位)
		buf[3] = GetFouthByteFromInt(type);//包类型(低位)
		buf[4] = GetTrdByteFromInt(len);//包体长度(高位)
		buf[5] = GetFouthByteFromInt(len);//包体长度(低位)
		buf[6] = 0;//校验码
		return buf;
	}

	int CDemoProtocolMgr::GetDataLen(BYTE buf[], int len)
	{
		if (len >= m_nPackageHeadLen)
		{
			return MergeByte(buf[5], buf[4]);
		}
		else
		{
			return 0;
		}
	}

	int CDemoProtocolMgr::GetPackageType(BYTE buf[], int len)
	{
		if (len >= m_nPackageHeadLen)
		{
			int type = MergeByte(buf[3], buf[2]);
			return DemoPackageType(type);
		}
		else
		{
			return DemoPackageType(m_nPackageHeadLen);
		}
	}

	bool CDemoProtocolMgr::ValidateKeepAlivePackage(LPPackageBase data)
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

	bool CDemoProtocolMgr::ValidatePackageType(int type)
	{
		bool b = false;
		if (true)//具体根据包类型来验证
		{
			if (type == Login || type == LoginReply || type == KeepAlive)
			{
				b = true;
			}
		}
		return b;
	}

	void CDemoProtocolMgr::OnSendBufReadyCmp(BYTE* buf, int len)
	{
		BYTE code = m_entrypy.Encrypt(buf + GetHeadLen(), len - GetHeadLen());
		buf[6] = code;
	}

	bool CDemoProtocolMgr::OnRecvBufReadyCmp(BYTE* buf, int len)
	{
		BYTE code = buf[6];
		return m_entrypy.DeEncrypt(buf + GetHeadLen(), len - GetHeadLen(), code);
	}

	void CDemoProtocolMgr::OnTcpConnectSuccess()
	{
		wchar_t pwd[8] = L"abcdefg";//协议密码
		int len = 0;
		BYTE* buf = WriteUTF8Str(pwd, &len);
		m_tcp.SendData(buf, len);
		ProtocolLoginPackage pack1;
		pack1.nKeepAlive = 1;
		pack1.nServerID = 1;
		pack1.nType = 16;
		pack1.nVersion = 0x007;
		pack1.str = L"";
		SendData(DemoPackageType::ProtocolLogin, &pack1);
		CProtocolMgr::OnTcpConnectSuccess();
	}
}