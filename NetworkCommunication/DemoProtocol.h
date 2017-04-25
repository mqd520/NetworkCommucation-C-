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

		Login = 511,//登录请求包
		LoginReply = 512//登录应答包
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

	//登录请求包
	typedef struct tagLoginPackage :public PackageBase
	{
		wchar_t strUsername[15];//用户名
		wchar_t strPwd[15];//密码
	}LoginPackage, *LPLoginPackage;

	//登录应答包
	typedef	struct tagLoginReplyPackage :public PackageBase
	{
		bool b;//登录是否成功
		wchar_t msg[30];//错误信息
	}LoginReplyPackage, *LPLoginReplyPackage;


	/////////////////////////////////包管理定义/////////////////////////////////////////
	//协议登录包管理
	class CProtocolLoginPackageMgr :public CCommonPackageMgr < ProtocolLoginPackage >
	{
		BYTE* Unparse(void* data, int* len);
		void* Parse(BYTE* buf, int len);
		void Release(void* data);
	};
}