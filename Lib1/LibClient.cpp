#include "stdafx.h"
#include "Def.h"
#include "Include/Lib1/Lib1Tool.h"
#include "Include/Lib1/LibClient.h"
#include "Include/Lib1/Packet.h"

#include "tc/TimerMoudleMgr.h"
#include "tc/NetworkStreamWrite.h"
#include "tc/ConnDisconnectEvt.h"
#include "tc/ConnectSrvResultEvt.h"
#include "tc/RecvDataEvt.h"
#include "tc/RecvNewConnEvt.h"

namespace lib1
{
	void OnTimer1(Timer* pTimer, int count, void* pParam1, void* pParam2);

	LibClient::LibClient(EServiceType type /*= EServiceType::None*/, bool bNeedVertify /*= true*/, string ip /*= ""*/, int port /*= 0*/) :
		TcpClient(ip, port),
		LibSrv1(type, this, ELibSrvType::Client),
		bNeedVertify(bNeedVertify)
	{
		t1.SetTimeout(Lib1_KeepAliveTimespan1);
		t1.SetCallback(OnTimer1, this);

		t2.SetTimeout(Lib1_KeepAliveTimespan2);
		t2.SetCallback(OnTimer1, this);
	}

	LibClient::~LibClient()
	{

	}

	void LibClient::SendPwd()
	{
		if (bNeedVertify)	// 需要发送客户端密码
		{
			BYTE* pBuf = (BYTE*)Lib1_ConnectPwd;
			int len = strlen(Lib1_ConnectPwd) + 1;

			TcpClient::Send(pBuf, len);
			LibSrv1::WriteLog(ETcpLogType::Info, "send login pwd to %s:%d, cur server type: %d", strIP.c_str(), nPort, (int)srvType);
		}
	}

	void LibClient::SendLoginSrvRequest()
	{
		LoginSrRequestPck pck;
		pck.cbCurrentServerType = (int)srvType;
		pck.cbRequestServerID = Lib1_ServerId;
		pck.cbKeepAlive = Lib1_keepAlive;
		pck.nVersion = Lib1_Version;
		pck.strGuid = Lib1Tool::CreateGUID();

		LibClient::SendPck(pck);
		LibSrv1::WriteLog(ETcpLogType::Info, "send login server request to %s:%d, cur server type: %d", strIP.c_str(), nPort, (int)srvType);
	}

	void LibClient::SendKeepAlive()
	{
		KeepAlivePck pck;
		pck.cbKeepAlive = 0;

		LibClient::SendPck(pck);
		t1.Run();
		t2.Stop();

		LibSrv1::WriteLog(ETcpLogType::Info, "send KeepAlive to %s:%d, cur server type: %d", strIP.c_str(), nPort, (int)srvType);
	}

	void LibClient::OnTimerKeepAlive(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		if (pTimer == &t1)
		{
			t1.Stop();
			LibSrv1::WriteLog(ETcpLogType::Warn, "miss KeepAlive from %s:%d, cur server type: %d", strIP.c_str(), nPort, (int)srvType);
			TcpClient::Close();
		}
		else if (pTimer == &t2)
		{
			t2.Stop();
			SendKeepAlive();
		}
	}

	void LibClient::OnRecvTcpEvent(TcpEvt* pEvt)
	{
		TcpClient::OnRecvTcpEvent(pEvt);
		LibSrv1::OnRecvTcpEvent(pEvt);
	}

	void LibClient::OnConnectCpl(TcpEvt* pEvt)
	{
		t1.Stop();
		t2.Stop();

		ConnectSrvResultEvt* pEvt1 = static_cast<ConnectSrvResultEvt*>(pEvt);
		if (pEvt1->GetConnectResult())
		{
			SendPwd();
			SendLoginSrvRequest();
		}
	}

	void LibClient::OnConnDiconnect(TcpEvt* pEvt)
	{
		t1.Stop();
		t2.Stop();
	}

	void LibClient::OnRecvPeerData(TcpEvt* pEvt)
	{
		RecvDataEvt* pEvt1 = static_cast<RecvDataEvt*>(pEvt);
		BYTE* pBuf = pEvt1->GetRecvBuf();
		int len = pEvt1->GetBufLen();

		ProcessRecvBuf(pBuf, len);
	}

	void LibClient::OnLoginSrvResult(PacketData& data)
	{
		LoginSrResultPck pck(data.pBuf, data.nLen, false);
		LibSrv1::WriteLog(ETcpLogType::Info, "login server success: %s:%d", strIP.c_str(), nPort);
		SendKeepAlive();
	}

	void LibClient::OnKeepAlive(PacketData& data)
	{
		t1.Stop();
		t2.Run();

		LibSrv1::WriteLog(ETcpLogType::Info, "recv KeepAlive from %s:%d, cur server type: %d", strIP.c_str(), nPort, (int)srvType);
	}

	void LibClient::SendPck(PacketBase& pck)
	{
		LibSrv1::SendPck1(pck);
	}

	void LibClient::Exit()
	{
		TcpClient::Exit();

		t1.Stop();
		t2.Stop();
		TimerMoudleMgr::GetTimerMgr()->Remove(&t1);
		TimerMoudleMgr::GetTimerMgr()->Remove(&t2);
	}




	void OnTimer1(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		TimerCallback_PacketClient::OnTimer(pTimer, count, pParam1, pParam2);
	}

	void TimerCallback_PacketClient::OnTimer(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		if (pParam1)
		{
			LibClient* p = static_cast<LibClient*>(pParam1);
			p->OnTimerKeepAlive(pTimer, count, pParam1, pParam2);
		}
	}
}