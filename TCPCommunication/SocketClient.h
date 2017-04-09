#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <string>

using namespace std;

namespace TCPCommunication
{
	//函数指针:收到tcp数据
	typedef void(*LPOnRecvSocketData)(BYTE buf[], int len);

	//TcpClient客户端类
	class CSocketClient
	{
	private:
		//线程信息
		typedef struct tagThreadInfo
		{
			HANDLE hThread;
			DWORD nThreadID;
		}ThreadInfo;

	protected:
		const TCHAR* m_strServerIP;//服务端IP
		int m_nServerPort;//服务端端口
		bool m_bIsCleaned;//是否已清理
		bool m_bIsConnected;//是否已经连接上服务端
		TCHAR* m_strLastError;//最后一次错误信息
		SOCKADDR_IN m_addrSrv;//服务端地址
		SOCKET m_socket;//客户端Socket
		ThreadInfo m_readThreadInfo;//数据读取线程信息
		bool m_bInited;//初始化
		LPOnRecvSocketData m_lpOnRecvData;//数据回调指针
		TCHAR* m_strClientIP;//客户端IP
		int m_nClientPort;//客户端端口
		int m_nSocketBufLen;//接收缓冲区大小
		char* m_pRecvBuf;//接收缓冲区

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
		// Method:    写入一行日志
		// FullName:  TCPCommunication::CSocketClient::WriteLine
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		// Parameter: string log
		//************************************
		virtual void WriteLine(string log);

		//************************************
		// Method:    清理线程
		// FullName:  TCPCommunication::CSocketClient::CleanThread
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CleanThread();

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
		// Parameter: 回调函数指针
		//************************************
		virtual void Init(const TCHAR* ip, int port, LPOnRecvSocketData lpfn, int socketBufLen = 1024);

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
		// Method:    开始连接服务端
		// FullName:  TCPCommunication::CSocketClient::StartConnect
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool StartConnect();

		//************************************
		// Method:    关闭与服务端连接
		// FullName:  TCPCommunication::CSocketClient::CloseConnect
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CloseConnect();

		//************************************
		// Method:    获取最后一次错误信息
		// FullName:  TCPCommunication::CSocketClient::GetLastError
		// Access:    public 
		// Returns:   TCHAR*
		// Qualifier:
		//************************************
		virtual TCHAR* GetLastError();

		//************************************
		// Method:    获取服务端Socket
		// FullName:  TCPCommunication::CSocketClient::GetServerSocket
		// Access:    public 
		// Returns:   SOCKET
		// Qualifier:
		//************************************
		virtual SOCKET GetServerSocket();

		//************************************
		// Method:    socket数据接收处理
		// FullName:  TCPCommunication::CSocketClient::OnRecvData
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 字节数组
		// Parameter: 字节数组长度
		//************************************
		virtual void OnRecvData(BYTE buf[], int len);

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
		// Method:    是否已初始化
		// FullName:  TCPCommunication::CSocketClient::IsInited
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool IsInited();

		//************************************
		// Method:    获取接收缓冲区
		// FullName:  TCPCommunication::CSocketClient::GetRecvBuf
		// Access:    virtual public 
		// Returns:   缓冲区
		// Qualifier:
		// Parameter: 缓冲区大小(输出)
		//************************************
		virtual char* GetRecvBuf(int *len);
	};
}