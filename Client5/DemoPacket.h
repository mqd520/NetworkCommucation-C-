#pragma once

#include <vector>
#include "PacketBase.h"
#include "PacketHeadBase.h"

using namespace std;
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
			ServiceLoginReply = 9,//服务登录应答

			DealerLogin = 511,//荷官登陆
			DealerLoginResult = 512//荷官登陆
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
	class classname:public PacketBase{\
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
		void Release();};

	//心跳包
	Packet_Declare_Begin(KeepAlivePack)
		BYTE n = 0;
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

		//荷官登录包
		Packet_Declare_Begin(DealerLoginPack)
		wchar_t* strName;//用户名
	wchar_t* strPwd;//密码
	int nTableID;//台面ID
	vector<wchar_t*> vecMac;//mac地址集合
	INT64 DealerSSID;//ssid
	Packet_Declare_End

		//荷官登录结果包
		Packet_Declare_Begin(DealerLoginResultPack)
	int nTableID;//台面ID
	int nResult;//登陆结果
	int nReloginCode;//重新登陆码
	Packet_Declare_End
}