#include "stdafx.h"
#include "DemoProtocolClient.h"
#include "MemoryTool.h"

using namespace NetworkCommunication;

namespace DemoProtocolMgr
{
	CDemoProtocolClient::CDemoProtocolClient()
	{
		//����
		m_pHead = new DemoPacketHead();//ָ����ͷ

		//�Ǳ���
		m_nKeepAlive = DemoPacketCmd::KeepAlive;//ָ������������
		m_pKeepAlive = new KeepAlivePack();//ָ��������
		m_nKeepAliveFailMaxCount = 3;//ָ������������ʧ�����ֵ
		m_nKeepAliveTimespan = 2 * 1000;//ָ�����������ʱ��
		m_nReconnectServerMaxCount = 3;//ָ�����������ߺ���������

	}

	CDemoProtocolClient::~CDemoProtocolClient()
	{

	}

	void CDemoProtocolClient::OnBeforeSendPack(int cmd, BYTE* buf, int len)
	{
		BYTE code = m_entrypy.Encrypt(buf + m_nPackageHeadLen, len - m_nPackageHeadLen);
		buf[6] = code;
	}

	bool CDemoProtocolClient::OnRecvCmpPacket(BYTE* buf, int len)
	{
		BYTE code = buf[6];
		return m_entrypy.DeEncrypt(buf + m_nPackageHeadLen, len - m_nPackageHeadLen, code);
	}

	void CDemoProtocolClient::OnTcpConnectSuccess(TCHAR* msg)
	{
		CProtocolClientMgr::OnTcpConnectSuccess(msg);

		//������֤��
		char pwd[8] = "abcdefg";//Э������
		int len = 0;
		BYTE* buf = WriteMultiByteStr(pwd, &len);
		m_tcp.SendData(buf, len);//��������
		delete buf;

		//���ͷ����½��
		ServiceLoginPack pack;
		pack.cbCurrentServerType = 16;
		pack.cbKeepAlive = 1;
		pack.cbRequestServerID = 1;
		pack.nVersion = 0x007;
		pack.strGuid = "";
		SendPack(&pack);
	}

	bool CDemoProtocolClient::PreprocessPack(int cmd, BYTE* buf, int len)
	{
		if (cmd == DemoPacketCmd::ServiceLoginReply)
		{
			TCHAR str[50];
			wsprintf(str, _T("Success to login server: %s:%d \n"), m_strServerIP, m_nServerPort);
			Printf(str);
			StartKeepAlive();//��ʼ����
			SendProtocolEvt(CProtocolClientMgr::LoginServerSuccess, NULL);
			return false;
		}
		return CProtocolClientMgr::PreprocessPack(cmd, buf, len);
	}
}