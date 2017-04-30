#include "stdafx.h"
#include "DemoProtocolClient.h"
#include "MemoryTool.h"

using namespace NetworkCommunication;

namespace DemoProtocolMgr
{
	CDemoProtocolClient::CDemoProtocolClient()
	{
		//必需
		m_pHead = new DemoPacketHead();//指定包头

		//非必需
		m_nKeepAlive = DemoPacketCmd::KeepAlive;//指定心跳包命令
		m_pKeepAlive = new KeepAlivePack();//指定心跳包
		m_nKeepAliveFailMaxCount = 3;//指定心跳包允许失败最大值
		m_nKeepAliveTimespan = 2 * 1000;//指定心跳包间隔时间
		m_nReconnectServerMaxCount = 3;//指定服务器断线后重连次数

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

		//发送验证码
		char pwd[8] = "abcdefg";//协议密码
		int len = 0;
		BYTE* buf = WriteMultiByteStr(pwd, &len);
		m_tcp.SendData(buf, len);//发送密码
		delete buf;

		//发送服务登陆包
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
			StartKeepAlive();//开始心跳
			SendProtocolEvt(CProtocolClientMgr::LoginServerSuccess, NULL);
			return false;
		}
		return CProtocolClientMgr::PreprocessPack(cmd, buf, len);
	}
}