#include "stdafx.h"
#include "SocketClient.h"
#include "NetTool.h"
#include "Common.h"

namespace TCPCommunication
{
	//开始读取数据
	DWORD WINAPI StartReadData(LPVOID lpParam);

	CSocketClient::CSocketClient()
	{
		m_strServerIP = NULL;
		m_nServerPort = 0;
		m_bIsCleaned = false;
		m_bIsConnected = false;
		m_strLastError = NULL;
		m_socket = NULL;
		memset(&m_addrSrv, 0, sizeof(SOCKADDR_IN));
		memset(&m_readThreadInfo, 0, sizeof(ThreadInfo));
	}

	CSocketClient::~CSocketClient()
	{
		Dispose();
	}

	//初始化
	void CSocketClient::Init(const TCHAR* ip, int port, LPOnRecvTCPData lpfn)
	{
		m_bInited = true;
		m_strServerIP = ip;
		m_nServerPort = port;
		m_strClientIP = NULL;
		m_nClientPort = 0;
		m_lpOnRecvData = lpfn;
	}

	//初始化Socket
	bool CSocketClient::InitSocket()
	{
		WSADATA wsaData;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			_tprintf(_T("Socket初始化失败!\n"));
			return false;
		}

		//创建服务端地址
		m_addrSrv.sin_family = AF_INET;
		m_addrSrv.sin_port = htons(m_nServerPort);
#ifdef _UNICODE
		string strTmp = UTF8ToMultiByte(m_strServerIP);
		m_addrSrv.sin_addr.S_un.S_addr = inet_addr(strTmp.c_str());
#else
		m_addrSrv.sin_addr.S_un.S_addr = inet_addr(m_strServerIP);
#endif

		//创建客户端Socket
		m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		SetAddressBySocket(m_socket);
		if (m_socket == INVALID_SOCKET)
		{
			_tprintf(_T("创建Socket失败: %d\n"), WSAGetLastError());
			CleanSocket();
			return false;
		}

		return true;
	}

	//清理资源
	void CSocketClient::CleanSocket()
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
	bool CSocketClient::StartConnect()
	{
		if (InitSocket())
		{
			int result = connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
			if (result == SOCKET_ERROR)
			{
				_tprintf(_T("连接服务端失败: %s:%d\n"), m_strServerIP, m_nServerPort);
				CleanSocket();
				return false;
			}
			m_readThreadInfo.hThread = ::CreateThread(NULL, 0, StartReadData, this, NULL, &m_readThreadInfo.nThreadID);
			return true;
		}
		return false;
	}

	//获取最后一次错误信息
	TCHAR* CSocketClient::GetLastError()
	{
		return m_strLastError;
	}

	//关闭与服务端连接
	void CSocketClient::CloseConnect()
	{
		closesocket(m_socket);
	}

	void CSocketClient::WriteLine(string log)
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
	SOCKET CSocketClient::GetServerSocket()
	{
		return m_socket;
	}

	//开始读取数据
	DWORD WINAPI StartReadData(LPVOID lpParam)
	{
		CSocketClient* pTCPClient = (CSocketClient*)lpParam;
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
	void CSocketClient::OnRecvData(BYTE buf[], int len)
	{
		if (m_lpOnRecvData)
		{
			//BYTE* buf1 = new BYTE[len];
			//memcpy(buf1, buf, len);
			try
			{
				//m_lpOnRecvData(buf, len, m_strClientIP, m_nClientPort);
				m_lpOnRecvData(buf, len);
				//if (buf1)
				//{
				//	delete buf1;
				//}
			}
			catch (int)
			{
				//delete buf1;
			}
		}
	}

	//清理线程
	void CSocketClient::CleanThread()
	{
		if (m_readThreadInfo.hThread > 0)
		{
			::TerminateThread(m_readThreadInfo.hThread, 0);
			::CloseHandle(m_readThreadInfo.hThread);
			m_readThreadInfo = { 0 };
		}
	}

	//主动释放资源
	void CSocketClient::Dispose()
	{
		CleanSocket();
		CleanThread();
	}

	//发送数据
	bool CSocketClient::SendData(BYTE buf[], int len)
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
	bool CSocketClient::IsInited()
	{
		return m_bInited;
	}

	bool CSocketClient::SetAddressBySocket(SOCKET socket)
	{
		SOCKADDR_IN address;
		memset(&address, 0, sizeof(address));
		int nAddrLen = sizeof(address);

		if (::getpeername(socket, (SOCKADDR*)&address, &nAddrLen) != 0)
		{
			return false;
		}

#ifdef _UNICODE
		char* tmp = inet_ntoa(address.sin_addr);
		wstring str = MultiByteToUTF8(tmp);
		m_strClientIP = (TCHAR*)str.c_str();
		delete tmp;
#else
		m_strClientIP = (TCHAR*)inet_ntoa(address.sin_addr);
#endif // _UNICODE

		m_nClientPort = (int)ntohs(address.sin_port);

		return true;
	}
}