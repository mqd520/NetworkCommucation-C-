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
		//************************************
		static void RegErrorCallback(LPErrorCallback lpfn, void* lpParam);

		//************************************
		// Method:    移除回调函数指针
		//************************************
		static void RemoveErrorCallback(LPErrorCallback lpfn);

		static bool Init(bool b = true);

		static void Release();

		static SOCKET CreateTcpSocket(bool b = true);

		static SOCKADDR_IN GetSocketAddr(string ip, int port);

		static bool Bind(SOCKET socket, string ip, int port, bool b = true);

		static string GetPeerIpAndPort(SOCKET socket, int* port);

		//************************************
		// Method:    获取本地IP
		//************************************
		static string GetLocalIP();
	};
}