#pragma once

#include <minwindef.h>
#include "Def.h"

namespace NetworkCommunication
{
	//包类型
	enum DemoPackageType
	{
		KeepAlive = 1,//心跳包
		ProtocolLogin = 8,//协议登录
		ProtocolLoginReply = 9,//协议登录应答

		Other = 100
	};


	/////////////////////////////////包体定义/////////////////////////////////////////
	//心跳包
	typedef	struct tagKeepAlivePackage :public PackageBase
	{
		BYTE n = 0;
	}KeepAlivePackage, *LPKeepAlivePackage;

	//协议登录包
	typedef	struct tagProtocolLoginPackage :public PackageBase
	{
		BYTE cbCurrentServerType;
		BYTE cbRequestServerID;
		BYTE cbKeepAlive;
		INT32 nVersion;
		char* strGuid;
	}ProtocolLoginPackage, *LPProtocolLoginPackage;

	//协议登录应答包
	typedef	struct tagProtocolLoginReplyPackage :public PackageBase
	{
		BYTE cbVerifyCode;//验证码
		int nServerID;//服务器ID
	}ProtocolLoginReplyPackage, *LPProtocolLoginReplyPackage;


	/////////////////////////////////包管理定义/////////////////////////////////////////
	//协议登录包管理
	class CProtocolLoginPackageMgr :public CCommonPackageMgr < ProtocolLoginPackage >
	{
		BYTE* Unparse(void* data, int* len);
		void* Parse(BYTE* buf, int len);
		void Release(void* data);
	};

	//协议登录应答包管理
	class CProtocolLoginReplyPackageMgr :public CCommonPackageMgr < ProtocolLoginReplyPackage >
	{
		BYTE* Unparse(void* data, int* len);
		void* Parse(BYTE* buf, int len);
		void Release(void* data);
	};
}