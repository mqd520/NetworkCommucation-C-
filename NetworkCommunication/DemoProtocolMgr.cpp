#include "stdafx.h"
#include "DemoProtocolMgr.h"
#include "ProtocolTool.h"
#include "NetTool.h"

namespace NetworkCommunication
{
#define DemoProtocol_HeadLen	7	//Э��ͷ����

	CDemoProtocolMgr::CDemoProtocolMgr()
	{
		//����
		m_nPackageHeadLen = DemoProtocol_HeadLen;//ָ����ͷ����

		// �Ǳ���
		m_nKeepAlive = DemoPackageType::KeepAlive;//ָ������������(��-999)
		m_pKeepAlive = new KeepAlivePackage();//ָ��������
		m_nKeepAliveFailMaxCount = 3;//ָ������������ʧ�����ֵ
		m_nKeepAliveTimespan = 2 * 1000;//ָ�����������ʱ��
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
		buf[0] = 127;//���汾��
		buf[1] = 104;//�ΰ汾��
		buf[2] = GetTrdByteFromInt(type);//������(��λ)
		buf[3] = GetFouthByteFromInt(type);//������(��λ)
		buf[4] = GetTrdByteFromInt(len);//���峤��(��λ)
		buf[5] = GetFouthByteFromInt(len);//���峤��(��λ)
		buf[6] = 0;//У����
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
		wchar_t pwd[8] = L"abcdefg";//Э������
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