#pragma once

#include <minwindef.h>
#include "PacketBase.h"
#include "PacketHeadBase.h"

using namespace NetworkCommunication;

namespace DemoProtocolMgr
{
	/////////////////////////////////包命令定义/////////////////////////////////////////
	class DemoPacketCmd
	{
	public:
		enum
		{
			KeepAlive = 1,//心跳包
			ServiceLogin = 8,//服务登录
			ServiceLoginReply = 9//服务登录应答
		};
	};

	/////////////////////////////////包头定义/////////////////////////////////////////
#define DemoPacketHead_Mask 32616		//包头标记
#define DemoPacketHead_Len (2+2+2+1)	//包头长度
	class DemoPacketHead :public PacketHeadBase
	{
	public:
		DemoPacketHead();
		~DemoPacketHead();

	protected:
		short nMask;//包头标记
		short nCmd;//包命令
		short nLen;//包头+包体总长度
		BYTE cbCode;//验证码

	public:
		int GetHeadLen();
		int GetPacketLen();
		int GetTotalLen();
		int GetCmd();
		BYTE* Read(int cmd, int len);
		void Write(BYTE* buf, int len);
		bool IsValid();
	};

	/////////////////////////////////包体定义/////////////////////////////////////////
#define Packet_Declare_Begin(classname)\
	class classname:public PacketBase\
								{\
	public:\
		classname();\
		~classname();\
		\
	public:\

#define Packet_Declare_End\
	public:\
		int GetCmd();\
		BYTE* Read(int* len);\
		void Write(BYTE* buf, int len);\
		void Release();\
								};

	//心跳包
	Packet_Declare_Begin(KeepAlivePack)
		BYTE n;
	Packet_Declare_End

		//服务登陆包
		Packet_Declare_Begin(ServiceLoginPack)
		BYTE cbCurrentServerType;
	BYTE cbRequestServerID;
	BYTE cbKeepAlive;
	int nVersion;
	char* strGuid = NULL;
	Packet_Declare_End

		//服务登陆应答包
		Packet_Declare_Begin(ServiceLoginReplyPack)
		BYTE cbVerifyCode;//验证码
	int nServerID;//服务器ID
	Packet_Declare_End
}