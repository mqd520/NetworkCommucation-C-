#pragma once
#include "Def.h"
#include "Include/Lib1/Def1.h"

#include "tc/Def1.h"
#include "tc/PacketBase.h"
#include "tc/TcpClient.h"
#include "tc/TcpServer.h"
#include "tc/TcpEvt.h"
#include "tc/MemoryStream.h"

using namespace tc;

namespace lib1
{
	class LibSrv1
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: type:	服务类型
		//************************************
		LibSrv1(EServiceType type = EServiceType::None, void* pObj = NULL, ELibSrvType type1 = ELibSrvType::Client);
		virtual ~LibSrv1();

	private:
		void* pObj;					// 
		ELibSrvType libSrvType;		// 服务器类型

	protected:
		EServiceType srvType;		// 服务类型
		MemoryStream ms;			// 内存流对象

	private:
		string GetIp1();
		int GetPort1();

	protected:
		//************************************
		// Method:    日志事件处理
		// Parameter: type:	tcp日志类型
		// Parameter: log:	日志内容
		//************************************
		virtual void OnLog(ETcpLogType type, string log);

		//************************************
		// Method:    收到tcp事件处理
		// Parameter: tcp事件
		//************************************
		void OnRecvTcpEvent(TcpEvt* pEvt);

		//************************************
		// Method:    处理接收缓冲区数据
		// Parameter: pBuf:		缓冲区
		// Parameter: len:		缓冲区长度
		// Parameter: clientId:	客户端id
		//************************************
		void ProcessRecvBuf(BYTE* pBuf, int len, int clientId = 0);

		//************************************
		// Method:    解析包缓冲区
		//************************************
		vector<PacketData> ParsePacketBuf();

		//************************************
		// Method:    连接服务端完成事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnConnectCpl(TcpEvt* pEvt);

		//************************************
		// Method:    连接断开事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnConnDiconnect(TcpEvt* pEvt);

		//************************************
		// Method:    收到新连接事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvConnection(TcpEvt* pEvt);

		//************************************
		// Method:    收到对端数据事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvPeerData(TcpEvt* pEvt);

		//************************************
		// Method:    处理包事件处理程序
		// Parameter: data:	包数据
		//************************************
		virtual void OnProcessPck(PacketData& data);

		//************************************
		// Method:    处理业务包事件处理程序
		// Parameter: data:	包数据
		//************************************
		virtual void OnProcessBusinessPck(PacketData& data);

		//************************************
		// Method:    心跳包事件处理程序
		// Parameter: data:	包数据
		//************************************
		virtual void OnKeepAlive(PacketData& data);

		//************************************
		// Method:    登录服务端请求包事件处理程序
		// Parameter: data:	包数据
		//************************************
		virtual void OnLoginSrvRequest(PacketData& data);

		//************************************
		// Method:    登录服务端结果包事件处理程序
		// Parameter: data:	包数据
		//************************************
		virtual void OnLoginSrvResult(PacketData& data);

		//************************************
		// Method:    发包
		//************************************
		virtual void SendPck1(PacketBase& pck, int clientId = 0);

	public:
		//************************************
		// Method:    获取服务类型
		//************************************
		virtual EServiceType GetSrvType();

		//************************************
		// Method:    日志事件处理
		// Parameter: type:	tcp日志类型
		// Parameter: log:	日志内容
		//************************************
		virtual void WriteLog(ETcpLogType type, string format, ...);
	};
}