#include "stdafx.h"
#include "Include/pck/ServerSession.h"
#include "pwd.hpp"
#include "Include/pck/Def.h"
#include "Include/pck/IGPacketSrvServer.h"

#include "tc/TcpLog.h"
#include "tc/TimerMoudleMgr.h"
using namespace tc;

namespace pck
{
	ServerSession::ServerSession(int clientId, void* pObj, bool recvPwd /*= true*/) :
		KeepAliveServer(clientId, PCR_KeepAlive_RecvTimespan, PCR_KeepAlive_Timeout, PCR_KeepAlive_MaxMissCount),

		nClientId(clientId),
		bRecvPwd(recvPwd),
		pObj(pObj),
		bVertified(false)
	{

		tVertify.SetTimeout(PCR_Connect_Timeout);
		auto fun1 = std::bind(&ServerSession::OnTimerVertify, this, _1, _2, _3, _4);
		tVertify.SetCallback(fun1, NULL, NULL);
		tVertify.Run();

		__super::AttachObj(pObj, NULL);

		strIp = KeepAliveServer::GetPeerIp();
		nPort = KeepAliveServer::GetPeerPort();
	}

	ServerSession::~ServerSession()
	{

	}

	void ServerSession::OnTimerVertify(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		tVertify.Stop();
		TcpLog::WriteLine(ETcpLogType::Error, "vertify pwd and login server request timeout: %s:%d", strIp.c_str(), nPort);

		if (pObj)
		{
			((IGPacketSrvServer*)pObj)->OnSessionClose(nClientId);
		}
	}

	void ServerSession::AttachObj(void* pObj)
	{
		ServerSession::pObj = pObj;
		KeepAliveServer::pObj1 = pObj;
	}

	bool ServerSession::OnRecvPeerData(RecvPeerDataEvt* pEvt)
	{
		if (IsVertified())
		{
			return true;
		}
		else
		{
			int len = strlen(PCR_ConnectPwd) + 1;
			if (pEvt->GetBufLen() >= len)
			{
				char ch[50] = { 0 };
				pEvt->Read((BYTE*)ch, len);

				if (strcmp(ch, PCR_ConnectPwd) == 0)
				{
					bVertified = true;
				}
			}

			TcpLog::WriteLine(bVertified ? ETcpLogType::Info : ETcpLogType::Error,
				"vertify pwd %s: %s:%d", bVertified ? "success" : "fail", strIp.c_str(), nPort);

			if (pEvt->GetBufLen() > 0)	// 指示缓冲区还有数据, 需要进一步进行处理
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	void ServerSession::OnConnDisconnect(ConnDisconnectEvt* pEvt)
	{
		__super::CloseKeepAlive();
	}

	void ServerSession::OnLoginSrvRequest(PacketData& data, bool b /*= true*/)
	{
		if (b)
		{
			tVertify.Stop();
			__super::StartKeepAlive();
		}
	}

	void ServerSession::SendKeepAlive(int clientId /*= 0*/)
	{
		if (pObj)
		{
			((IGPacketSrvServer*)pObj)->SendKeepAlive(clientId);
		}

		__super::SendKeepAlive(clientId);
	}

	void ServerSession::OnMissKeepAlive(int count, bool b /*= true*/)
	{
		__super::OnMissKeepAlive(count, b);

		if (pObj)
		{
			((IGPacketSrvServer*)pObj)->OnMissKeepAlive(nClientId, count, b);
		}
	}

	void ServerSession::OnRecvKeepAlive()
	{
		__super::OnKeepAlive();
	}

	int ServerSession::GetClientId() const
	{
		return nClientId;
	}

	string ServerSession::GetIp() const
	{
		return strIp;
	}

	int ServerSession::GetPort() const
	{
		return nPort;
	}

	bool ServerSession::IsVertified()
	{
		if (bRecvPwd)
		{
			return bVertified;
		}

		return true;
	}

	void ServerSession::Close()
	{
		KeepAliveServer::Exit();
		tVertify.Stop();
		TimerMoudleMgr::GetTimerMgr()->Remove(&tVertify);
	}
}