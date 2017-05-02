#pragma once

#include "ProtocolClientMgr.h"
#include "EncryptBuffer.h"
#include "DemoPacket.h"

using namespace NetworkCommunication;

namespace DemoProtocolMgr
{
	//Demo协议客户端管理
	class CDemoProtocolClient :public CProtocolClientMgr
	{
	public:
		CDemoProtocolClient();
		~CDemoProtocolClient();

	protected:
		CEncryptBuffer m_entrypy;//字节加密对象

	protected:
		void OnBeforeSendPack(int cmd, BYTE* buf, int len);
		bool OnRecvCmpPacket(BYTE* buf, int len);
		void OnTcpConnectSuccess(TCHAR* msg);
		bool PreprocessPack(int cmd, BYTE* buf, int len);
	};
}