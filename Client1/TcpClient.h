#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <string>

using namespace std;

#define TCPClientRecvMsg	(WM_USER+1000)

//线程信息
typedef struct tagThreadInfo
{
	HANDLE hThread;
	DWORD nThreadID;
}ThreadInfo;

//TcpClient客户端类
class CTcpClient
{
public:
	CTcpClient(HWND hwnd, const TCHAR* ip, int port);
	~CTcpClient();

	//连接到服务端
	bool StartConnect();
	//关闭与服务端连接
	void CloseConnect();
	//获取最后一次错误信息
	TCHAR* GetLastError();
	//获取Socket
	SOCKET GetServerSocket();
	//接收数据
	void OnRecvData(char* buf);
	//主动释放资源
	void Dispose();
protected:
	HWND m_hwnd;//关联的窗口句柄
	const TCHAR* m_strIP;//IP
	int m_nPort;//端口
	bool m_bIsCleaned;//是否已清理
	bool m_bIsConnected;//是否已经连接上服务端
	TCHAR* m_strLastError;//最后一次错误信息
	SOCKADDR_IN m_addrSrv;//服务端地址
	SOCKET m_socket;//客户端Socket
	ThreadInfo m_readThreadInfo;//数据读取线程信息


	//初始化
	bool Init();
	//清理Socket
	void CleanSocket();
	//写入一行日志
	void WriteLine(string log);
	//清理线程
	void CleanThread();
};