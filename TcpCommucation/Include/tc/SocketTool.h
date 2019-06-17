#pragma once
#include <WinSock2.h>
#include <string>
#include <vector>

using namespace std;

namespace tc
{
	// 回调函数原型
	// string err:		错误信息
	// void* lpParam:	附加参数
	typedef void(*LPErrorCallback)(string err, void* lpParam);

	// 回调信息
	typedef struct tagSocketCallbackInfo
	{
		LPErrorCallback lpfn;	// 回调函数指针
		void* lpParam;			// 附加参数
	}SocketCallbackInfo;

	// socket工具类
	class SocketTool
	{
	public:
		SocketTool();
		~SocketTool();

	private:
		static vector<SocketCallbackInfo> vecFNs;	// 回调信息集合

	private:
		//************************************
		// Method:    处理错误信息
		// Parameter: fn:		函数名字
		// Parameter: code:		系统错误码
		// Parameter: remark:	备注信息
		// Parameter: b:		是否处理
		//************************************
		static void ProcessErrorInfo(string fn, int code, string remark = "", bool b = true);

	public:
		//************************************
		// Method:    注册回调函数指针
		// Parameter: lpfn:	回调函数指针
		// Parameter: lpParam: 附加参数
		//************************************
		static void RegErrorCallback(LPErrorCallback lpfn, void* lpParam);

		//************************************
		// Method:    移除回调函数指针
		// Parameter: lpfn:	回调函数指针
		//************************************
		static void RemoveErrorCallback(LPErrorCallback lpfn);

		//************************************
		// Method:    初始化
		//************************************
		static bool Init(bool b = true);

		//************************************
		// Method:    释放资源
		//************************************
		static void Release();

		//************************************
		// Method:    创建一个SOCKET
		//************************************
		static SOCKET CreateTcpSocket(bool b = true);

		//************************************
		// Method:    获取SOCKADDR_IN
		//************************************
		static SOCKADDR_IN GetSocketAddr(string ip, int port);

		//************************************
		// Method:    bind socket
		//************************************
		static bool Bind(SOCKET socket, string ip, int port, bool b = true);

		//************************************
		// Method:    开始监听服务端
		// Parameter: socket: socket
		// Parameter: ip: 服务端IP
		// Parameter: port: 服务端端口
		//************************************
		static bool Listen(SOCKET socket, string ip, int port, int backlog = SOMAXCONN, bool b = true);

		//************************************
		// Method:    接收新连接
		// Parameter: ip: 服务端IP
		// Parameter: port: 服务端端口
		//************************************
		static SOCKET Accept(SOCKET socket, string ip, int port, bool b = true);

		//************************************
		// Method:    接收数据
		// Return:	  连接是否正常
		// Parameter: socket: socket
		// Parameter: pBuf: 接收数据缓冲区指针
		// Parameter: len: 接收数据缓冲区长度
		// Parameter: actuallyLen: 实际接收长度
		//************************************
		static bool Recv(SOCKET socket, BYTE* pBuf, int len, int* actuallyLen, bool b = true);

		//************************************
		// Method:    发送数据
		// Parameter: socket: socket
		// Parameter: pBuf: 发送数据缓冲区指针
		// Parameter: len: 发送数据缓冲区长度
		// Parameter: actuallyLen: 实际发送长度
		//************************************
		static bool Send(SOCKET socket, BYTE* pBuf, int len, int* actuallyLen, bool b = true);

		//************************************
		// Method:    连接服务端
		// Parameter: socket: socket
		// Parameter: ip: 服务端IP
		// Parameter: port: 服务端端口
		//************************************
		static bool Connect(SOCKET socket, string ip, int port, bool b = true);

		//************************************
		// Method:    查找信号
		//************************************
		static int Select(int nfds, fd_set* readfds, fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout, bool b = true);

		//************************************
		// Method:    关闭socket
		//************************************
		static void ShutDown(SOCKET socket, int how = SD_BOTH, bool b = true);

		//************************************
		// Method:    关闭socket
		//************************************
		static bool CloseSocket(SOCKET socket, bool b = true);

		//************************************
		// Method:    设置socket非阻塞
		//************************************
		static void SetNonBlock(SOCKET socket, bool nonblock = true);

		//************************************
		// Method:    获取socket状态
		//************************************
		static bool GetSocketOpt(SOCKET socket, char* optval, int* optlen, bool b = true);

		//************************************
		// Method:    获取对端socket的ip和端口
		//************************************
		static string GetPeerIpAndPort(SOCKET socket, int* port);

		//************************************
		// Method:    获取本地IP
		//************************************
		static string GetLocalIP();
	};
}