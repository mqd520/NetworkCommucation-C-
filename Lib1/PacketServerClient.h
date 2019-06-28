#pragma once
#include "Include/Lib1/Def1.h"
#include "tc/TcpClient.h"
#include "tc/Timer.h"

using namespace tc;

namespace lib1
{
	// 服务端客户端类
	class PacketServerClient
	{
	public:
		PacketServerClient(int clientId, void* pSrv, bool bNeedVertify = true);
		virtual ~PacketServerClient();

	protected:
		int nClientId;		// client id
		void* pSrv;			// LibServer
		bool bNeedVertify;	// 是否需要客户端发送密码
		bool bVertified;	// 是否已验证客户端密码
		int nMissCount;		// 连续丢失心跳包的次数
		Timer	t1;			// 密码定时器
		Timer	t2;			// 发送登录服务请求包定时器
		Timer	t3;			// 心跳包定时器

	public:
		//************************************
		// Method:    获取客户端id
		//************************************
		int GetClientId();
		
		//************************************
		// Method:    获取是否验证已通过
		//************************************
		bool IsVertified();

		//************************************
		// Method:    创建客户端事件处理
		//************************************
		void OnCreate();

		//************************************
		// Method:    客户端关闭事件处理
		//************************************
		void OnClose();

		//************************************
		// Method:    验证密码事件处理
		// Return:	  是否继续处理
		// Parameter: pBuf:		缓冲区
		// Parameter: len:		缓冲区长度
		//************************************
		void OnVertifyPwd(BYTE* pBuf, int len);

		//************************************
		// Method:    登录服务端请求事件处理程序
		// Parameter: data:	包数据
		//************************************
		void OnLoginSrvRequest(PacketData& data);

		//************************************
		// Method:    心跳包事件处理程序
		// Parameter: data:	包数据
		//************************************
		void OnKeepAlive(PacketData& data);

		//************************************
		// Method:    丢失心跳包事件处理程序
		//************************************
		void OnMissKeepAlive();

		void OnTimer(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);
	};


	class TimerCallback_PacketServerClient
	{
	public:
		static void OnTimer(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);
	};
}