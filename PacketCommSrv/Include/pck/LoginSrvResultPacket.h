#pragma once
#include "PacketCmd.h"

#include "tc/Packet.h"
using namespace tc;

namespace pck
{
	// 登录服务端结果包
	class LoginSrvResultPacket : public Packet
	{
	public:
		LoginSrvResultPacket();

	public:
		BYTE		cbVerifyCode;	// code
		INT32		nServerID;		// server id

	public:
		//************************************
		// Method:    获取包长度(不含包头)
		//************************************
		virtual int GetLen() override;

		//************************************
		// Method:    从流中读取数据到包中
		// Parameter: ns:	只读网络流对象
		//************************************
		virtual void Read(NetworkStreamRead& ns) override;

		//************************************
		// Method:    向流中写入数据
		// Parameter: ns:	只写网络流对象
		//************************************
		virtual void Write(NetworkStreamWrite& ns) override;
	};
}