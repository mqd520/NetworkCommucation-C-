#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <string>
#include <vector>

using namespace std;

namespace TCPCommunication
{
	//************************************
	// Method:    收到socket数据
	// FullName:  TCPCommunication::LPOnRecvSocketData
	// Access:    public 
	// Returns:   指示调用是否已释放缓冲区
	// Qualifier: 缓冲区
	// Parameter: 缓冲区长度
	//************************************
	typedef bool(*LPOnRecvSocketData)(BYTE buf[], int len);

	//事件类型
	enum SocketClientEvtType
	{
		Info,//消息
		error,//错误
		disconnected,//失去服务端连接
		connected,//连接上服务端
		Debug//其它
	};

	//消息通知结构体
	typedef struct tagNotifyEvt
	{
		bool haveMsg;//是否有事件
		SocketClientEvtType type;//事件类型
		TCHAR* msg;//消息
	}NotifyEvt, *LPNotifyEvt;

	//************************************
	// Method:    收到socket客户端事件函数指针
	// FullName:  TCPCommunication::LPOnRecvNotifyEvt
	// Access:    public 
	// Returns:   是否已处理
	// Qualifier: 事件类型
	// Parameter: 消息
	//************************************
	typedef bool(*LPOnRecvNotifyEvt)(SocketClientEvtType type, TCHAR* msg);

	//线程循环信息
	typedef struct tagThreadWhileInfo
	{
		bool bReadSocketData;
		bool bConnectServer;
		bool bReadCatchSocketData;
		bool bReadNotifyEvt;
	}ThreadWhileInfo, *LPThreadWhileInfo;

	//Socket客户端类
	class CSocketClient
	{
	private:
		//线程信息
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//句柄
			DWORD nThreadID;//ID
			bool bPause;//是否已暂停
		}ThreadInfo, *LPThreadInfo;

		//缓存Socket缓冲区信息
		typedef struct tagCatchSocketBufInfo
		{
			int adress;//指针地址
			int len;//缓冲区长度
		}CatchSocketBufInfo, *LPCatchSocketBufInfo;

		//失去服务端连接原因枚举
		enum LoseConnectReason
		{
			Server,//服务端主动断开
			Client,//客户端主动断开
			Net//网络故障
		};

	protected:
		const TCHAR* m_strServerIP;//服务端IP
		int m_nServerPort;//服务端端口
		bool m_bIsCleaned;//是否已清理
		SOCKADDR_IN m_addrSrv;//服务端地址
		SOCKET m_socket;//客户端Socket
		ThreadInfo m_tiReadSocketData;//读取socket数据线程信息
		bool m_bInited;//是否初始化
		LPOnRecvSocketData m_lpfnOnRecvSocketData;//接收socket数据回调函数
		TCHAR* m_strClientIP;//客户端IP
		int m_nClientPort;//客户端端口
		int m_nRecvSocketBufLen;//接收Socket缓冲区总长度
		char* m_pRecvSocketBuf;//接收Socket缓冲区
		NotifyEvt m_evt;//事件
		ThreadInfo m_tiReadNotifyEvt;//读取通知消息线程信息
		LPOnRecvNotifyEvt m_lpfnOnRecvNotifyEvt;//接收通知消息回调函数
		const int m_msgbufsize = 1024;//通知消息缓冲区大小
		vector<CatchSocketBufInfo> m_vecCatchRecvSocketBuf;//缓存接收缓冲区集合
		ThreadInfo m_tiReadCatchSocketData;//读取缓存socket数据线程信息
		bool m_bHaslpfnRecvSocketData;//是否已有接收socket数据回调函数
		ThreadInfo m_tiConnectServer;//连接服务端线程信息
		bool m_bConnected;//是否已连接上服务端
		int m_nReconnectTimeSpan;//连接失败后间隔时间(毫秒)
		int m_nReconnectTimes;//允许重连次数(0:一直连接)(默认1)
		int m_nReconnected;//断开后已重连次数
		bool m_bReconnecting;//正在重新连接
		bool m_bAutoReconnect;//断线后是否自动重新连接
		ThreadWhileInfo m_whileinfo;//线程循环信息

	protected:
		//************************************
		// Method:    初始化socket
		// FullName:  TCPCommunication::CSocketClient::InitSocket
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void InitSocket();

		//************************************
		// Method:    初始化客户端socket
		// FullName:  TCPCommunication::CSocketClient::InitSocket
		// Access:    protected 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void CreateClientSocket();

		//************************************
		// Method:    重新连接服务端
		// FullName:  TCPCommunication::CSocketClient::ReconnectServer
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void ReconnectServer();

		//************************************
		// Method:    清理Socket
		// FullName:  TCPCommunication::CSocketClient::CleanSocket
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CleanSocket();

		//************************************
		// Method:    清理线程
		// FullName:  TCPCommunication::CSocketClient::CleanThread
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CleanThread();

		//************************************
		// Method:    保存通知事件
		// FullName:  TCPCommunication::CSocketClient::SaveNotifyEvt
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: 类型
		// Parameter: 消息
		//************************************
		virtual void SaveNotifyEvt(SocketClientEvtType type, TCHAR* msg);

		//************************************
		// Method:    设置客户端IP和端口
		// FullName:  CSocketClient::SetAddressBySocket
		// Access:    protected 
		// Returns:   bool
		// Qualifier:
		// Parameter: SOCKET socket
		//************************************
		virtual bool SetAddressBySocket(SOCKET socket);

		//************************************
		// Method:    打印消息
		// FullName:  TCPCommunication::CSocketClient::Printf
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: 消息
		//************************************
		virtual void Printf(TCHAR* msg);

		//************************************
		// Method:    发送接收到的socket数据到调用者
		// FullName:  TCPCommunication::CSocketClient::SendRecvData
		// Access:    virtual protected 
		// Returns:   指示调用是否已释放缓冲区
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual bool SendRecvData(BYTE buf[], int len);

		//************************************
		// Method:    创建后台线程
		// FullName:  TCPCommunication::CSocketClient::CreateThread
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CreateThread();

		//************************************
		// Method:    失去服务端连接
		// FullName:  TCPCommunication::CSocketClient::OnLoseConnect
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: 原因
		//************************************
		virtual void OnLoseConnect(LoseConnectReason reason);

		//************************************
		// Method:    暂停(恢复)线程
		// FullName:  TCPCommunication::CSocketClient::PauseThread
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: 是否暂停
		// Parameter: 线程信息
		//************************************
		virtual void PauseThread(bool pause, LPThreadInfo ti);

		//************************************
		// Method:    已连接上服务端
		// FullName:  TCPCommunication::CSocketClient::OnConnected
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnConnected();

	public:
		CSocketClient();
		~CSocketClient();

		//************************************
		// Method:    初始化
		// FullName:  TCPCommunication::CSocketClient::Init
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 服务端IP
		// Parameter: 服务端端口
		// Parameter: 接收消息回调函数
		// Parameter: 回调函数指针
		//************************************
		virtual void Init(const TCHAR* ip, int port, LPOnRecvNotifyEvt lpfnOnRecvNotifyEvt = NULL, int socketBufLen = 1024,
			bool autoReconnect = true, int reconnectTimes = 3, int reconnectTimeSpan = 1500);

		//************************************
		// Method:    设置接收socket数据回调函数
		// FullName:  TCPCommunication::CSocketClient::SetCallback
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: 接收socket数据回调函数
		//************************************
		virtual void SetCallback(LPOnRecvSocketData lpfnOnRecvSocketData);

		//************************************
		// Method:    连接服务端
		// FullName:  TCPCommunication::CSocketClient::Connect
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void Connect();

		//************************************
		// Method:    强制重新连接服务端
		// FullName:  TCPCommunication::CSocketClient::Reconnect
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Reconnect();

		//************************************
		// Method:    连接服务端
		// FullName:  TCPCommunication::CSocketClient::ConnectServer
		// Access:    virtual protected 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void ConnectServer();

		//************************************
		// Method:    关闭与服务端连接
		// FullName:  TCPCommunication::CSocketClient::CloseConnect
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CloseConnect();

		//************************************
		// Method:    获取服务端Socket
		// FullName:  TCPCommunication::CSocketClient::GetServerSocket
		// Access:    public 
		// Returns:   SOCKET
		// Qualifier:
		//************************************
		virtual SOCKET GetClientSocket();

		//************************************
		// Method:    读取Socket数据
		// FullName:  TCPCommunication::CSocketClient::OnRecvSocketData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual void ReadSocketData();

		//************************************
		// Method:    获取线程循环信息
		// FullName:  TCPCommunication::CSocketClient::GetWhileInfo
		// Access:    virtual public 
		// Returns:   TCPCommunication::CSocketClient::ThreadWhileInfo
		// Qualifier:
		//************************************
		virtual ThreadWhileInfo GetWhileInfo();

		//************************************
		// Method:    主动释放资源
		// FullName:  TCPCommunication::CSocketClient::Dispose
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Dispose();

		//************************************
		// Method:    发送数据
		// FullName:  TCPCommunication::CSocketClient::SendData
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: 字节数组
		// Parameter: 字节数组长度
		//************************************
		virtual bool SendData(BYTE buf[], int len);

		//************************************
		// Method:    读取通知消息并发送给调用者
		// FullName:  TCPCommunication::CSocketClient::NotifyMsg
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void ReadNotifyEvt();

		//************************************
		// Method:    读取缓存Socket数据并发送给调用者
		// FullName:  TCPCommunication::CSocketClient::SendSocketData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void ReadCatchSocketData();

		//************************************
		// Method:    获取连接状态
		// FullName:  TCPCommunication::CSocketClient::GetConnectStatus
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool GetConnectStatus();

		//************************************
		// Method:    模拟一次服务端发包
		// FullName:  TCPCommunication::CSocketClient::SimularServerData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual void SimulateServerData(BYTE* buf, int len);
	};
}