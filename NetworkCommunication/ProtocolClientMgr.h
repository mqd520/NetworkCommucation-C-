#pragma once

#include <tchar.h>
#include "ByteStream.h"
#include "PacketBase.h"
#include "PacketHeadBase.h"
#include "OtherTool.h"
#include "TcpClientT.h"

namespace NetworkCommunication
{
	//协议客户端管理
	class CProtocolClientMgr
	{
	public:
		//协议管理事件类型
		enum ProtocolEvtType
		{
			fatal,//严重错误
			tcpfailed,//tcp连接失败
			tcpsuccess,//tcp连接成功
			NetError,//网络错误
			serverdis,//服务端断开连接
			Info,//消息
			LoginServerSuccess,//协议登录成功
			LoginServerFailed,//协议登录失败
			LoseServer//失去服务端(心跳包检测失败)
		};

	protected:
		//************************************
		// Method:    接收包体函数指针
		// Qualifier: 包命令
		// Parameter: 包体缓冲区指针
		// Parameter: 包体缓冲区长度
		//************************************
		typedef void(*LPOnRecvPack)(int cmd, BYTE* buf, int len);

		//************************************
		// Method:    收到协议事件处理
		// Qualifier: 事件类型
		// Parameter: 消息
		//************************************
		typedef void(*LPOnRecvProtocolEvt)(ProtocolEvtType type, TCHAR* msg);

		//线程信息
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//线程句柄
			DWORD dwThreadID;//线程ID
		}ThreadInfo, *LPThreadInfo;

	protected:
		CTcpClientT<CProtocolClientMgr> m_tcp;//tcp客户端对象
		CByteStream* m_stream;//字节流对象
		LPOnRecvPack m_lpfnRecvData;//收到包体数据函数指针
		int m_nPackageHeadLen;//包头长度
		int m_nKeepAlive;//心跳包命令
		HANDLE m_hMutexStream;//字节流互斥对象
		int m_nKeepAliveTimespan;//心跳包间隔时间
		bool m_bRecvKeepAlive;//是否已收到心跳包
		int m_nKeepAliveFailCount;//心跳包失败计数,0代表已收到对方心跳包
		int m_nKeepAliveFailMaxCount;//心跳包失败计数最大值,超过值后认为对方已掉线
		int m_nReconnectServerMaxCount;//失去服务端连接(非tcp连接,检测不到指定次数的心跳包),自动重连的最大值(0:无限制)
		int m_nReconnectServerCount;//失去服务端连接后,已连接服务端的次数
		PacketBase* m_pKeepAlive;//心跳包指针
		PacketHeadBase* m_pHead;//包头指针
		LPOnRecvProtocolEvt m_lpfnRecvProtocolEvt;//收到协议事件函数指针
		int m_nStreamBufLen;//流缓冲区长度
		int m_nTcpBufLen;//tcp接收缓冲区长度
		bool m_bAutoReconnect;//是否自动重连
		int m_nReconnectTimes;//允许重连次数
		int m_nReconnectTimeSpan;//重连间隔时间
		int m_nConnectTimeout;//连接超时时间
		TcpDataRecvType m_sendType;//tcp数据发送方式
		CTimerT<CProtocolClientMgr>* m_timer;//心跳包定时器
		TCHAR m_strServerIP[20];//服务端IP
		int m_nServerPort;//服务端端口

	protected:
		//************************************
		// Method:    包头无效事件处理
		//************************************
		virtual void OnPackageHeadInvalid();

		//************************************
		// Method:    接收数据事件处理
		// Returns:   是否已释放缓冲区
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual bool OnRecvData(BYTE buf[], int len);

		//************************************
		// Method:    通知接收者有包体数据到来
		// Parameter: 包命令
		// Parameter: 包体缓冲区
		// Parameter: 包体缓冲区长度
		//************************************
		virtual void NotifyRecver(int cmd, BYTE* buf, int len);

		//************************************
		// Method:    开始解包(循环从流中解包,直到流中长度不足包头长度)
		//************************************
		virtual void StartUnpacket();

		//************************************
		// Method:    预处理包
		// Returns:   是否需要调用者处理
		// Parameter: 包命令
		// Parameter: 包缓冲区
		// Parameter: 包缓冲区长度
		//************************************
		virtual bool PreprocessPack(int cmd, BYTE* buf, int len);

		//************************************
		// Method:    封包
		// Returns:   包缓冲区
		// Parameter: 包体指针
		// Parameter: 包缓冲区长度
		//************************************
		BYTE* Pack(PacketBase* data, int * len);

		//************************************
		// Method:    接收tcp事件处理
		// Returns:   是否已处理
		// Parameter: 事件类型
		// Parameter: 消息
		//************************************
		void OnRecvTcpEvt(TcpEvtType type, TCHAR* msg);

		//************************************
		// Method:    tcp连接成功事件处理
		// Parameter: 消息
		//************************************
		virtual void OnTcpConnectSuccess(TCHAR* msg);

		//************************************
		// Method:    tcp连接失败事件处理
		// Parameter: 消息
		//************************************
		virtual void OnTcpConnectFail(TCHAR* msg);

		//************************************
		// Method:    服务端断开连接事件处理
		// Parameter: 消息
		//************************************
		virtual void OnServerDisconnect(TCHAR* msg);

		//************************************
		// Method:    失去服务端事件处理
		// Parameter: 消息
		//************************************
		virtual void OnLoseServer();

		//************************************
		// Method:    发送协议事件
		// Parameter: 事件类型
		// Parameter: 消息
		//************************************
		void SendProtocolEvt(ProtocolEvtType type, TCHAR* msg);

		//************************************
		// Method:    发包前事件处理
		// Parameter: 包命令
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual void OnBeforeSendPack(int cmd, BYTE* buf, int len);

		//************************************
		// Method:    接收到一个完整包事件处理
		// Returns:   包是否有效
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual bool OnRecvCmpPacket(BYTE* buf, int len);

		//************************************
		// Method:    是否指定了心跳包
		// Returns:   是否指定了心跳包
		//************************************
		bool IsAssignedKeepAlive();

		//************************************
		// Method:    开始心跳包处理
		//************************************
		void StartKeepAlive();

		//************************************
		// Method:    心跳包超时事件处理
		//************************************
		bool OnKeepAliveTimeout();

		//************************************
		// Method:    重新连接
		//************************************
		void Reconnect();

		//发送心跳包
		virtual void SendKeepAlivePack();

	public:
		CProtocolClientMgr();
		~CProtocolClientMgr();

		//************************************
		// Method:    初始化
		// Parameter: 服务端IP
		// Parameter: 服务端端口
		// Parameter: 接收包函数指针
		// Parameter: 接收协议事件函数指针
		//************************************
		virtual void Init(TCHAR* ip, int port, LPOnRecvPack lpfnRecvData, LPOnRecvProtocolEvt lpfnRecvProtocolEvt = NULL);

		//************************************
		// Method:    连接服务端
		//************************************
		void Connect();

		//************************************
		// Method:    发包
		// Returns:   是否成功
		// Parameter: 包体指针
		//************************************
		bool SendPack(PacketBase* data);

		//************************************
		// Method:    发送缓冲区
		// Returns:   是否发送成功
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		bool SendData(BYTE* buf, int len);

		//************************************
		// Method:    关闭连接
		//************************************
		void CloseConnect();

		//************************************
		// Method:    获取tcp客户端对象
		//************************************
		CTcpClient GetTcpClientObj();

		//************************************
		// Method:    模拟一次服务端发包
		// Parameter: 包体结构体指针
		//************************************
		void SimulateServerData(PacketBase* data);
	};
}