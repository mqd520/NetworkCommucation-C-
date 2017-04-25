#include "stdafx.h"
#include "DemoProtocolMgr.h"
#include "ByteStream.h"
#include "MemoryTool.h"

namespace NetworkCommunication
{
#define DemoProtocol_HeadLen	7	//Э��ͷ����

	CDemoProtocolMgr::CDemoProtocolMgr()
	{
		//����
		m_nPackageHeadLen = DemoProtocol_HeadLen;//ָ����ͷ����

		//�Ǳ���
		m_nKeepAlive = DemoPackageType::KeepAlive;//ָ������������(��-999)
		m_pKeepAlive = new KeepAlivePackage();//ָ��������
		m_nKeepAliveFailMaxCount = 3;//ָ������������ʧ�����ֵ
		m_nKeepAliveTimespan = 2 * 1000;//ָ�����������ʱ��
	}

	CDemoProtocolMgr::~CDemoProtocolMgr()
	{

	}

	void CDemoProtocolMgr::AssociatePackageType()
	{
		m_vecPackageMgr.push_back({ DemoPackageType::KeepAlive, new CCommonPackageMgr<KeepAlivePackage>() });
		m_vecPackageMgr.push_back({ DemoPackageType::ProtocolLogin, new CProtocolLoginPackageMgr() });

		m_vecPackageMgr.push_back({ DemoPackageType::Login, new CCommonPackageMgr<LoginPackage>() });
		m_vecPackageMgr.push_back({ DemoPackageType::LoginReply, new CCommonPackageMgr<LoginReplyPackage>() });
	}

	BYTE* CDemoProtocolMgr::GetPackageHeadBuf(int type, int len)
	{
		BYTE* buf = new BYTE[m_nPackageHeadLen];
		CByteStream s(20);
		s.WriteShort(32616);
		s.WriteShort(type);
		s.WriteShort(len);
		s.WriteByte(0);
		memcpy(buf, s.GetBuf(), m_nPackageHeadLen);
		return buf;
	}

	int CDemoProtocolMgr::GetDataLen(BYTE buf[], int len)
	{
		if (len >= m_nPackageHeadLen)
		{
			return MergeByte(buf[4], buf[5]);
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
			int type = MergeByte(buf[2], buf[3]);
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
		if (true)//������ݰ�ͷ����֤
		{
			b = true;
		}
		return true;
	}

	bool CDemoProtocolMgr::ValidatePackageType(int type)
	{
		bool b = false;
		if (true)//������ݰ���������֤
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
		char pwd[8] = "abcdefg";//Э������
		int len = 0;
		BYTE* buf = WriteMultiByteStr(pwd, &len);
		m_tcp.SendData(buf, len);//��������
		delete buf;
		ProtocolLoginPackage pack1;
		pack1.cbCurrentServerType = 16;
		pack1.cbKeepAlive = 1;
		pack1.cbRequestServerID = 1;
		pack1.nVersion = 0x007;
		pack1.strGuid = "";
		SendData(DemoPackageType::ProtocolLogin, &pack1);//����Э���¼��
		CProtocolMgr::OnTcpConnectSuccess();
	}

	bool CDemoProtocolMgr::AnalyticsPackage(int type, LPPackageBase data)
	{
		if (type == -1)
		{
			return true;
		}
		return CProtocolMgr::AnalyticsPackage(type, data);
	}
}