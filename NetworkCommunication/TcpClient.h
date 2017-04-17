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
	//tcp事件类型
	enum TcpEvtType
	{
		error,//错误
		disconnected,//失去服务端连接
		connected//连接上服务端
	};

	//************************************
	// Method:    收到tcp数据函数指针
	// FullName:  NetworkCommunication::LPOnRecvTcpData
	// Access:    public 
	// Returns:   指示调用者是否已释放缓冲区
	// Qualifier: 缓冲区
	// Parameter: 缓冲区长度
	//************************************
	typedef bool(*LPOnRecvTcpData)(BYTE buf[], int len);

	//************************************
	// Method:    收到tcp事件函数指针
	// FullName:  NetworkCommunication::LPOnRecvTcpEvt
	// Access:    public 
	// Returns:   是否已处理
	// Qualifier: 事件类型
	// Parameter: 消息
	//************************************
	typedef bool(*LPOnRecvTcpEvt)(TcpEvtType type, TCHAR* msg);

	//tcp客户端
	class CTcpClient
	{
	private:
		//失去服务端连接原因枚举
		enum LoseConnectReason
		{
			Server,//服务端主动断开
			Client,//客户端主动断开
			Net//网络故障
		};

		//线程信息
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//线程句柄
			DWORD dwThreadID;//线程ID
		}ThreadInfo, *LPThreadInfo;

	protected:
		const TCHAR* m_strServerIP;//服务端IP
		int m_nServerPort;//服务端端口
		bool m_bIsCleaned;//是否已清理
		SOCKADDR_IN m_addrSrv;//服务端地址
		SOCKET m_socket;//客户端Socket
		bool m_bInited;//是否初始化
		LPOnRecvTcpData m_lpfnOnRecvTcpData;//接收tcp数据回调函数
		int m_nRecvTcpBufLen;//接收tcp缓冲区总长度
		char* m_pRecvTcpBuf;//接收tcp缓冲区
		LPOnRecvTcpEvt m_lpfnOnRecvTcpEvt;//接收tcp事件回调函数
		bool m_bHaslpfnRecvTcpData;//是否已有接收tcp数据回调函数
		int m_nReconnectTimeSpan;//连接失败后间隔时间(毫秒)
		int m_nReconnectTimes;//允许重连次数(0:一直连接)(默认1)
		int m_nReconnected;//断开后已重连次数
		bool m_bReconnecting;//正在重新连接
		bool m_bAutoReconnect;//断线后是否自动重新连接
		bool m_bExitThread;//指示应该退出后台线程
		int m_nConnectTimeout;//连接超时时间(0:无限制等待)
		ThreadInfo m_tiConnect;//连接线程信息
		ThreadInfo m_tiConnectTimeout;//连接超时线程信息
		bool m_bConnectedTimeout;//指示连接是否超时

	protected:
		//************************************
		// Method:    初始化socket
		// FullName:  NetworkCommunication::CTcpClient::InitSocket
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void InitSocket();

		//************************************
		// Method:    初始化客户端socket
		// FullName:  NetworkCommunication::CTcpClient::InitSocket
		// Access:    protected 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void CreateClientSocket();

		//************************************
		// Method:    重新连接服务端
		// FullName:  NetworkCommunication::CTcpClient::ReconnectServer
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void ReconnectServer();

		//************************************
		// Method:    清理Socket
		// FullName:  NetworkCommunication::CTcpClient::CleanSocket
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CleanSocket();

		//************************************
		// Method:    发送通知事件
		// FullName:  NetworkCommunication::CTcpClient::SaveNotifyEvt
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: 类型
		// Parameter: 消息
		//************************************
		virtual void SendTcpEvt(TcpEvtType type, TCHAR* msg);

		//************************************
		// Method:    打印消息
		// FullName:  NetworkCommunication::CTcpClient::Printf
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: 消息
		//************************************
		virtual void Printf(TCHAR* msg);

		//************************************
		// Method:    失去服务端连接
		// FullName:  NetworkCommunication::CTcpClient::OnLoseConnect
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: 原因
		//************************************
		virtual void OnLoseConnect(LoseConnectReason reason);

		//************************************
		// Method:    已连接上服务端
		// FullName:  NetworkCommunication::CTcpClient::OnConnected
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
		// FullName:  NetworkCommunication::CTcpClient::Init
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 服务端IP
		// Parameter: 服务端端口
		// Parameter: 接收消息回调函数
		// Parameter: 回调函数指针
		//************************************
		virtual void Init(const TCHAR* ip, int port, int socketBufLen = 1024, bool autoReconnect = true, int reconnectTimes = 0,
			int reconnectTimeSpan = 1500, int connectTimeout = 2000);

		//************************************
		// Method:    设置回调函数
		// FullName:  NetworkCommunication::CTcpClient::SetCallback
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: 接收socket数据回调函数
		//************************************
		virtual void SetCallback(LPOnRecvTcpData lpfnOnRecvTcpData, LPOnRecvTcpEvt lpfnOnRecvTcpEvt = NULL);

		//************************************
		// Method:    连接服务端
		// FullName:  NetworkCommunication::CTcpClient::Connect
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void Connect();

		//************************************
		// Method:    连接服务端
		// FullName:  NetworkCommunication::CTcpClient::ConnectServer
		// Access:    virtual protected 
		// Returns:   是否应该退出线程
		// Qualifier:
		//************************************
		virtual bool ConnectServer();

		//************************************
		// Method:    关闭与服务端连接
		// FullName:  NetworkCommunication::CTcpClient::CloseConnect
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CloseConnect();

		//************************************
		// Method:    获取服务端Socket
		// FullName:  NetworkCommunication::CTcpClient::GetServerSocket
		// Access:    public 
		// Returns:   SOCKET
		// Qualifier:
		//************************************
		virtual SOCKET GetClientSocket();

		//************************************
		// Method:    读取tcp数据
		// FullName:  NetworkCommunication::CTcpClient::ReadTcpData
		// Access:    virtual public 
		// Returns:   是否该退出线程
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual bool ReadTcpData();

		//************************************
		// Method:    发送数据
		// FullName:  NetworkCommunication::CTcpClient::SendData
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: 字节数组
		// Parameter: 字节数组长度
		// Parameter: 实际发送长度
		//************************************
		virtual bool SendData(BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    收到tcp数据
		// FullName:  NetworkCommunication::CTcpClient::OnRecvSocketData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual void OnRecvTcpData(BYTE buf[], int len);

		//************************************
		// Method:    连接超时
		// FullName:  NetworkCommunication::CTcpClient::OnConnectTimeout
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnConnectTimeout();

		//************************************
		// Method:    模拟一次服务端发包
		// FullName:  NetworkCommunication::CTcpClient::SimulateServerData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual void SimulateServerData(BYTE* buf, int len);
	};
}