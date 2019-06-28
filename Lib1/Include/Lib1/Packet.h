#pragma once
#include "tc/PacketBase.h"

using namespace tc;

namespace lib1
{
	// 心跳包
	class KeepAlivePck : public PacketBase
	{
	public:
		KeepAlivePck(BYTE* pBuf = NULL, int len = 0, bool bigEndian = true);
		~KeepAlivePck();

	public:
		BYTE cbKeepAlive;		// n1, 1个字节

	public:
		//************************************
		// Method:    获取包长度(不含包头)
		//************************************
		virtual int GetLen();

		//************************************
		// Method:    从流中读取数据到包中
		// Parameter: ns:	只读网络流对象
		//************************************
		virtual void Read(CNetworkStreamRead& ns) override;

		//************************************
		// Method:    向流中写入数据
		// Parameter: ns:	只写网络流对象
		//************************************
		virtual void Write(CNetworkStreamWrite& ns) override;
	};


	// 登录服务端请求包
	class LoginSrRequestPck : public PacketBase
	{
	public:
		LoginSrRequestPck(BYTE* pBuf = NULL, int len = 0, bool bigEndian = true);
		~LoginSrRequestPck();

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
		virtual void Read(CNetworkStreamRead& ns) override;

		//************************************
		// Method:    向流中写入数据
		// Parameter: ns:	只写网络流对象
		//************************************
		virtual void Write(CNetworkStreamWrite& ns) override;
	};



	// 登录服务端结果包
	class LoginSrResultPck : public PacketBase
	{
	public:
		LoginSrResultPck(BYTE* pBuf = NULL, int len = 0, bool bigEndian = true);
		~LoginSrResultPck();

	public:
		BYTE		cbVerifyCode;	// code, 1个字节
		INT32		nServerID;		// server id, 4个字节

	public:
		//************************************
		// Method:    获取包长度(不含包头)
		//************************************
		virtual int GetLen() override;

		//************************************
		// Method:    从流中读取数据到包中
		// Parameter: ns:	只读网络流对象
		//************************************
		virtual void Read(CNetworkStreamRead& ns) override;

		//************************************
		// Method:    向流中写入数据
		// Parameter: ns:	只写网络流对象
		//************************************
		virtual void Write(CNetworkStreamWrite& ns) override;
	};
}