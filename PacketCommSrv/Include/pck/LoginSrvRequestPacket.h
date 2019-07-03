#pragma once
#include "PacketCmd.h"

#include "tc/Packet.h"
using namespace tc;

namespace pck
{
	// 登录服务端请求包
	class LoginSrvRequestPacket : public Packet
	{
	public:
		LoginSrvRequestPacket();

	public:
		BYTE		cbCurrentServerType;	// 当前服务类型, 1个字节
		BYTE		cbRequestServerID;		// 请求的服务器id, 1个字节
		BYTE		cbKeepAlive;			// 心跳值, 1个字节
		INT32		nVersion;				// 版本, 4个字节
		string		strGuid;				// GUID

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