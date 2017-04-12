#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <string>
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	//事件类型
	enum SocketClientEvtType
	{
		Info,//消息
		error,//错误
		disconnected,//失去服务端连接
		connected,//连接上服务端
		Debug//其它
	};

	//************************************
	// Method:    收到socket数据
	// FullName:  NetworkCommunication::LPOnRecvSocketData
	// Access:    public 
	// Returns:   指示调用是否已释放缓冲区
	// Qualifier: 缓冲区
	// Parameter: 缓冲区长度
	//************************************
	typedef bool(*LPOnRecvSocketData)(BYTE buf[], int len);

	//************************************
	// Method:    收到socket客户端事件函数指针
	// FullName:  NetworkCommunication::LPOnRecvNotifyEvt
	// Access:    public 
	// Returns:   是否已处理
	// Qualifier: 事件类型
	// Parameter: 消息
	//************************************
	typedef bool(*LPOnRecvNotifyEvt)(SocketClientEvtType type, TCHAR* msg);

	//tcp客户端
	class CTcpClient
	{
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
		bool m_bInited;//是否初始化
		LPOnRecvSocketData m_lpfnOnRecvSocketData;//接收socket数据回调函数
		int m_nRecvSocketBufLen;//接收Socket缓冲区总长度
		char* m_pRecvSocketBuf;//接收Socket缓冲区
		LPOnRecvNotifyEvt m_lpfnOnRecvNotifyEvt;//接收通知事件回调函数
		bool m_bHaslpfnRecvSocketData;//是否已有接收socket数据回调函数
		bool m_bConnected;//是否已连接上服务端
		int m_nReconnectTimeSpan;//连接失败后间隔时间(毫秒)
		int m_nReconnectTimes;//允许重连次数(0:一直连接)(默认1)
		int m_nReconnected;//断开后已重连次数
		bool m_bReconnecting;//正在重新连接
		bool m_bAutoReconnect;//断线后是否自动重新连接
		bool m_bExitThread;//指示线程应该退出(只有析构函数被调用才赋值"true")

	protected:
		//************************************
		// Method:    初始化socket
		// FullName:  NetworkCommunication::CSocketClient::InitSocket
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void InitSocket();

		//************************************
		// Method:    初始化客户端socket
		// FullName:  NetworkCommunication::CSocketClient::InitSocket
		// Access:    protected 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void CreateClientSocket();

		//************************************
		// Method:    重新连接服务端
		// FullName:  NetworkCommunication::CSocketClient::ReconnectServer
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void ReconnectServer();

		//************************************
		// Method:    清理Socket
		// FullName:  NetworkCommunication::CSocketClient::CleanSocket
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CleanSocket();

		//************************************
		// Method:    发送通知事件
		// FullName:  NetworkCommunication::CSocketClient::SaveNotifyEvt
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: 类型
		// Parameter: 消息
		//************************************
		virtual void SendNotifyEvt(SocketClientEvtType type, TCHAR* msg);

		//************************************
		// Method:    打印消息
		// FullName:  NetworkCommunication::CSocketClient::Printf
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: 消息
		//************************************
		virtual void Printf(TCHAR* msg);

		//************************************
		// Method:    失去服务端连接
		// FullName:  NetworkCommunication::CSocketClient::OnLoseConnect
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: 原因
		//************************************
		virtual void OnLoseConnect(LoseConnectReason reason);

		//************************************
		// Method:    已连接上服务端
		// FullName:  NetworkCommunication::CSocketClient::OnConnected
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnConnected();

	public:
		CTcpClient();
		~CTcpClient();

		//************************************
		// Method:    初始化
		// FullName:  NetworkCommunication::CSocketClient::Init
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
		// FullName:  NetworkCommunication::CSocketClient::SetCallback
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: 接收socket数据回调函数
		//************************************
		virtual void SetCallback(LPOnRecvSocketData lpfnOnRecvSocketData);

		//************************************
		// Method:    连接服务端
		// FullName:  NetworkCommunication::CSocketClient::Connect
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void Connect();

		//************************************
		// Method:    强制重新连接服务端
		// FullName:  NetworkCommunication::CSocketClient::Reconnect
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Reconnect();

		//************************************
		// Method:    连接服务端
		// FullName:  NetworkCommunication::CSocketClient::ConnectServer
		// Access:    virtual protected 
		// Returns:   是否应该退出线程
		// Qualifier:
		//************************************
		virtual bool ConnectServer();

		//************************************
		// Method:    关闭与服务端连接
		// FullName:  NetworkCommunication::CSocketClient::CloseConnect
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CloseConnect();

		//************************************
		// Method:    获取服务端Socket
		// FullName:  NetworkCommunication::CSocketClient::GetServerSocket
		// Access:    public 
		// Returns:   SOCKET
		// Qualifier:
		//************************************
		virtual SOCKET GetClientSocket();

		//************************************
		// Method:    读取Socket数据
		// FullName:  NetworkCommunication::CSocketClient::OnRecvSocketData
		// Access:    virtual public 
		// Returns:   是否该退出线程
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual bool ReadSocketData();

		//************************************
		// Method:    发送数据
		// FullName:  NetworkCommunication::CSocketClient::SendData
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: 字节数组
		// Parameter: 字节数组长度
		//************************************
		virtual bool SendData(BYTE buf[], int len);

		//************************************
		// Method:    获取连接状态
		// FullName:  NetworkCommunication::CSocketClient::GetConnectStatus
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool GetConnectStatus();

		//************************************
		// Method:    收到socket数据
		// FullName:  NetworkCommunication::CSocketClient::OnRecvSocketData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: BYTE buf[]
		// Parameter: int len
		//************************************
		virtual void OnRecvSocketData(BYTE buf[], int len);

		//************************************
		// Method:    模拟一次服务端发包
		// FullName:  NetworkCommunication::CSocketClient::SimularServerData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual void SimulateServerData(BYTE* buf, int len);
	};
}