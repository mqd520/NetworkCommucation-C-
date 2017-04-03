#include "stdafx.h"
#include "TcpClient.h"
#include "NetTool.h"
#include "Common.h"

using namespace Common;

//开始读取数据
DWORD WINAPI StartReadData(LPVOID lpParam);

CTcpClient::CTcpClient()
{
	m_strIP = NULL;
	m_nPort = NULL;
	m_bIsCleaned = false;
	m_bIsConnected = false;
	m_strLastError = NULL;
	m_socket = NULL;
	memset(&m_addrSrv, 0, sizeof(SOCKADDR_IN));
}

CTcpClient::~CTcpClient()
{
	Dispose();
}

//初始化
void CTcpClient::Init(const TCHAR* ip, int port, LPOnRecvData lpfn)
{
	m_bInited = true;
	m_strIP = ip;
	m_nPort = port;
	m_lpOnRecvData = lpfn;
}

//初始化Socket
bool CTcpClient::InitSocket()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		_tprintf(_T("Socket初始化失败!\n"));
		return false;
	}

	//创建服务端地址
	m_addrSrv.sin_family = AF_INET;
	m_addrSrv.sin_port = htons(m_nPort);
#ifdef _UNICODE
	string strTmp = UTF8ToMultiByte(m_strIP);
	m_addrSrv.sin_addr.S_un.S_addr = inet_addr(strTmp.c_str());
#else
	m_addrSrv.sin_addr.S_un.S_addr = inet_addr(m_strIP);
#endif

	//创建客户端Socket
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		_tprintf(_T("创建Socket失败: %d\n"), WSAGetLastError());
		CleanSocket();
		return false;
	}

	return true;
}

//清理资源
void CTcpClient::CleanSocket()
{
	if (!m_bIsCleaned)
	{
		if (m_socket)
		{
			closesocket(m_socket);
		}
		WSACleanup();
		m_bIsCleaned = true;
	}
}

//连接到服务端
bool CTcpClient::StartConnect()
{
	if (InitSocket())
	{
		int result = connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
		if (result == SOCKET_ERROR)
		{
			_tprintf(_T("连接服务端失败: %s:%d\n"), m_strIP, m_nPort);
			CleanSocket();
			return false;
		}
		m_readThreadInfo.hThread = ::CreateThread(NULL, 0, StartReadData, this, NULL, &m_readThreadInfo.nThreadID);
		return true;
	}
	return false;
}

//获取最后一次错误信息
TCHAR* CTcpClient::GetLastError()
{
	return m_strLastError;
}

//关闭与服务端连接
void CTcpClient::CloseConnect()
{
	closesocket(m_socket);
}

void CTcpClient::WriteLine(string log)
{
#ifdef _DEBUG
#ifdef _CONSOLE
	_tprintf(log.c_str());
	_tprintf("\n");
#endif
#ifdef _WINDOWS
	TRACE(log.c_str());
	TRACE("\n");
#endif
#endif
}

//获取Socket
SOCKET CTcpClient::GetServerSocket()
{
	return m_socket;
}

//开始读取数据
DWORD WINAPI StartReadData(LPVOID lpParam)
{
	CTcpClient* pTCPClient = (CTcpClient*)lpParam;
	char buf[1024];
	while (true)
	{
		memset(buf, 0, sizeof(buf));
		int len = recv(pTCPClient->GetServerSocket(), buf, 1024, 0);
		if (len > 0)
		{
			pTCPClient->OnRecvData((BYTE*)buf, len);
		}
	}
	return 0;
}

//接收数据事件
void CTcpClient::OnRecvData(BYTE buf[], int len)
{
	if (m_lpOnRecvData)
	{
		BYTE* buf1 = new BYTE[len];
		memcpy(buf1, buf, len);
		try
		{
			m_lpOnRecvData(buf, len);
			if (buf1)
			{
				delete buf1;
			}
		}
		catch (int)
		{
			delete buf1;
		}
	}
}

//清理线程
void CTcpClient::CleanThread()
{
	if (m_readThreadInfo.hThread > 0)
	{
		::TerminateThread(m_readThreadInfo.hThread, 0);
		::CloseHandle(m_readThreadInfo.hThread);
		m_readThreadInfo = { 0 };
	}
}

//主动释放资源
void CTcpClient::Dispose()
{
	CleanSocket();
	CleanThread();
}

//发送数据
bool CTcpClient::SendData(BYTE buf[], int len)
{
	bool b = false;
	int sended = 0;
	while (true)
	{
		if (sended == len)
		{
			b = true;
			break;
		}
		int result = send(m_socket, (char*)buf, len - sended, 0);
		if (result == SOCKET_ERROR)
		{
			break;
		}
		else
		{
			sended += result;
		}
	}
	return b;
}

//是否已初始化
bool CTcpClient::IsInited()
{
	return m_bInited;
}