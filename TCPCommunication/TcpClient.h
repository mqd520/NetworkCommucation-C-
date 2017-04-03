#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <string>

using namespace std;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)	{if(p){delete p;p=NULL;}}
#endif // !SAFE_DELETE

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p){delete[] p;  p=NULL;} }
#endif // !SAFE_DELETE_ARRAY



//数据回调指针
typedef void(*LPOnRecvData)(BYTE buf[], int len);

//TcpClient客户端类
class CTcpClient
{
private:
	typedef struct tagThreadInfo
	{
		HANDLE hThread;
		DWORD nThreadID;
	}ThreadInfo;

public:
	CTcpClient();
	~CTcpClient();

	//初始化
	void Init(const TCHAR* ip, int port, LPOnRecvData lpfn = NULL);
	//连接到服务端
	bool StartConnect();
	//关闭与服务端连接
	void CloseConnect();
	//获取最后一次错误信息
	TCHAR* GetLastError();
	//获取Socket
	SOCKET GetServerSocket();
	//接收数据事件
	void OnRecvData(BYTE buf[], int len);
	//主动释放资源
	void Dispose();
	//发送数据
	bool SendData(BYTE buf[], int len);
	//是否已初始化
	bool IsInited();
protected:
	const TCHAR* m_strIP;//IP
	int m_nPort;//端口
	bool m_bIsCleaned;//是否已清理
	bool m_bIsConnected;//是否已经连接上服务端
	TCHAR* m_strLastError;//最后一次错误信息
	SOCKADDR_IN m_addrSrv;//服务端地址
	SOCKET m_socket;//客户端Socket
	ThreadInfo m_readThreadInfo;//数据读取线程信息
	bool m_bInited;//初始化
	LPOnRecvData m_lpOnRecvData;//数据回调指针

	//初始化
	bool InitSocket();
	//清理Socket
	void CleanSocket();
	//写入一行日志
	void WriteLine(string log);
	//清理线程
	void CleanThread();
};