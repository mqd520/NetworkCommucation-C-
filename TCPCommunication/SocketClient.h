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

	//Socket客户端类
	class CSocketClient
	{
	private:
		//线程信息
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//句柄
			DWORD nThreadID;//ID
		}ThreadInfo, *LPThreadInfo;

		//缓存Socket缓冲区信息
		typedef struct tagCatchSocketBufInfo
		{
			int adress;//指针地址
			int len;//缓冲区长度
		}CatchSocketBufInfo, *LPCatchSocketBufInfo;

	protected:
		const TCHAR* m_strServerIP;//服务端IP
		int m_nServerPort;//服务端端口
		bool m_bIsCleaned;//是否已清理
		bool m_bIsConnected;//是否已经连接上服务端
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

	protected:
		//************************************
		// Method:    初始化客户端socket
		// FullName:  TCPCommunication::CSocketClient::InitSocket
		// Access:    protected 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool InitSocket();

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
		virtual void Init(const TCHAR* ip, int port, LPOnRecvNotifyEvt lpfnOnRecvNotifyEvt = NULL, int socketBufLen = 1024);

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
		// Method:    连接服务端(阻塞)
		// FullName:  TCPCommunication::CSocketClient::Connect
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool Connect();

		//************************************
		// Method:    连接服务端(非阻塞)
		// FullName:  TCPCommunication::CSocketClient::ConnectUnasync
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool ConnectUnasync();

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