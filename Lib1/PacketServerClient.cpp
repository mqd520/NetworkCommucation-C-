#include "stdafx.h"
#include "PacketServerClient.h"
#include "Include/Lib1/LibServer.h"
#include "Include/Lib1/Packet.h"

#include "tc/RecvDataEvt.h"
#include "tc/TimerMoudleMgr.h"

namespace lib1
{
	void OnTimer2(Timer* pTimer, int count, void* pParam1, void* pParam2);

	PacketServerClient::PacketServerClient(int clientId, void* pSrv, bool bNeedVertify /*= true*/) :
		nClientId(clientId),
		bNeedVertify(bNeedVertify),
		bVertified(false),
		pSrv(pSrv),
		nMissCount(0)
	{
		t1.SetTimeout(Lib1_PwdTimeout);
		t1.SetCallback(OnTimer2, this);

		t2.SetTimeout(Lib1_LoginRequestTimeout);
		t2.SetCallback(OnTimer2, this);

		t3.SetTimeout(Lib1_KeepAliveTimespan1);
		t3.SetCallback(OnTimer2, this);
	}

	PacketServerClient::~PacketServerClient()
	{

	}

	int PacketServerClient::GetClientId()
	{
		return nClientId;
	}

	bool PacketServerClient::IsVertified()
	{
		if (bNeedVertify)
		{
			return bVertified;
		}

		return true;
	}

	void PacketServerClient::OnCreate()
	{
		nMissCount = 0;

		t1.Stop();
		t2.Stop();
		t3.Stop();

		if (bNeedVertify && bVertified == false)	// 需要客户端发送密码, 并且服务端还没有验证
		{
			t1.Run();
		}
	}

	void PacketServerClient::OnClose()
	{
		t1.Stop();
		t2.Stop();
		t3.Stop();

		TimerMoudleMgr::GetTimerMgr()->Remove(&t1);
		TimerMoudleMgr::GetTimerMgr()->Remove(&t2);
		TimerMoudleMgr::GetTimerMgr()->Remove(&t3);
	}

	void PacketServerClient::OnVertifyPwd(BYTE* pBuf, int len)
	{
		t1.Stop();
		string strPwd = (char*)pBuf;
		if (strPwd == Lib1_ConnectPwd)
		{
			t2.Run();
			bVertified = true;
			((LibServer*)pSrv)->WriteLog(ETcpLogType::Info, "vertify the pwd sent by client success, from: %s:%d", "192.168.0.111", 45678);
		}
		else
		{
			((LibServer*)pSrv)->WriteLog(ETcpLogType::Warn, "vertify the pwd sent by client fail, from: %s:%d", "192.168.0.111", 45678);
			((LibServer*)pSrv)->CloseClient(nClientId);		// 密码不正确, 断开与客户端的连接
		}
	}

	void PacketServerClient::OnLoginSrvRequest(PacketData& data)
	{
		t2.Stop();

		LoginSrResultPck pck;
		pck.cbVerifyCode = Lib1_VertifyCode;
		pck.nServerID = 1;

		((LibServer*)pSrv)->SendPck(pck, nClientId);
		((LibServer*)pSrv)->WriteLog(ETcpLogType::Info, "recv login server request from: %s:%d", "192.168.0.111", 45678);

		t3.Run();
	}

	void PacketServerClient::OnKeepAlive(PacketData& data)
	{
		nMissCount = 0;
		t3.Stop();

		KeepAlivePck pck;
		pck.cbKeepAlive = 1;
		((LibServer*)pSrv)->SendPck(pck, nClientId);

		((LibServer*)pSrv)->WriteLog(ETcpLogType::Info, "recv keepAlive from: %s:%d", "192.168.0.111", 45678);

		t3.Run();
	}

	void PacketServerClient::OnMissKeepAlive()
	{
		((LibServer*)pSrv)->OnMissKeepAlive(nClientId, nMissCount);
	}

	void PacketServerClient::OnTimer(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		if (pTimer == &t1)
		{
			t1.Stop();
			((LibServer*)pSrv)->WriteLog(ETcpLogType::Warn, "recv pwd sent by client timeout, from: %s:%d", "192.168.0.111", 567778);
			((LibServer*)pSrv)->CloseClient(nClientId);		// 没有在指定的时间内发送密码
		}
		else if (pTimer == &t2)
		{
			t2.Stop();
			((LibServer*)pSrv)->WriteLog(ETcpLogType::Warn, "recv login server request timeout, from: %s:%d", "192.168.0.111", 567778);
			((LibServer*)pSrv)->CloseClient(nClientId);		// 没有在指定的时间内发送服务登陆请求包
		}
		else if (pTimer == &t3)
		{
			nMissCount++;
			OnMissKeepAlive();

			if (nMissCount > Lib1_MaxMissCount)
			{
				((LibServer*)pSrv)->CloseClient(nClientId);	// 丢失心跳包次数超过最大值
			}
		}
	}




	void OnTimer2(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		TimerCallback_PacketServerClient::OnTimer(pTimer, count, pParam1, pParam2);
	}

	void TimerCallback_PacketServerClient::OnTimer(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		if (pParam1)
		{
			PacketServerClient* p = static_cast<PacketServerClient*>(pParam1);
			p->OnTimer(pTimer, count, pParam1, pParam2);
		}
	}
}