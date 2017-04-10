#include "stdafx.h"
#include "SocketClient.h"
#include "NetTool.h"
#include "Common.h"

namespace TCPCommunication
{
	//开始读取数据
	DWORD WINAPI StartReadData(LPVOID lpParam);

	//通知调用者消息
	DWORD WINAPI NotifyCallerMsg(LPVOID lpParam);

	CSocketClient::CSocketClient()
	{
		m_nSocketBufLen = 0;
		m_pRecvBuf = NULL;
		m_strServerIP = NULL;
		m_nServerPort = 0;
		m_bIsCleaned = false;
		m_bIsConnected = false;
		m_strLastError = NULL;
		m_socket = NULL;
		m_strClientIP = NULL;
		m_nClientPort = 0;
		memset(&m_addrSrv, 0, sizeof(SOCKADDR_IN));
		m_readThreadInfo = { 0 };
		m_notifyThreadInfo = { 0 };
		TCHAR* p = new TCHAR[m_msgbufsize];
		memset(p, 0, m_msgbufsize);
		m_msg.msg = p;
		m_msg.haveMsg = false;
		m_lpfnNotifyMsg = NULL;
	}

	CSocketClient::~CSocketClient()
	{
		if (m_pRecvBuf)
		{
			delete m_pRecvBuf;
			m_pRecvBuf = NULL;
		}
		if (m_msg.msg)
		{
			delete m_msg.msg;
		}
		Dispose();
	}

	void CSocketClient::Init(const TCHAR* ip, int port, LPOnRecvSocketData lpfn, LPOnRecvNotifyMsg lpfnMsg, int socketBufLen)
	{
		if (!m_bInited)
		{
			m_bInited = true;
			m_nSocketBufLen = socketBufLen;
			m_pRecvBuf = new char[socketBufLen];
			m_strServerIP = ip;
			m_nServerPort = port;
			m_lpOnRecvData = lpfn;
			m_lpfnNotifyMsg = lpfnMsg;
			if (m_lpfnNotifyMsg)
			{
				m_notifyThreadInfo.hThread = ::CreateThread(NULL, 0, NotifyCallerMsg, this, NULL, &m_notifyThreadInfo.nThreadID);
			}
		}
	}

	bool CSocketClient::InitSocket()
	{
		WSADATA wsaData;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			SetNotifyMsg(SocketClientMsgType::error, _T("Socket初始化失败!\n"));
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
			SetNotifyMsg(SocketClientMsgType::error, _T("创建Socket失败!\n"));
			CleanSocket();
			return false;
		}

		return true;
	}

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

	bool CSocketClient::StartConnect()
	{
		if (InitSocket())
		{
			int result = connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
			if (result == SOCKET_ERROR)
			{
				TCHAR s[100];
				wsprintf(s, _T("连接服务端失败: %s:%d\n"), m_strServerIP, m_nServerPort);
				SetNotifyMsg(SocketClientMsgType::error, s);
				CleanSocket();
				return false;
			}
			m_readThreadInfo.hThread = ::CreateThread(NULL, 0, StartReadData, this, NULL, &m_readThreadInfo.nThreadID);
			return true;
		}
		return false;
	}

	TCHAR* CSocketClient::GetLastError()
	{
		return m_strLastError;
	}

	void CSocketClient::CloseConnect()
	{
		closesocket(m_socket);
	}

	SOCKET CSocketClient::GetServerSocket()
	{
		return m_socket;
	}

	DWORD WINAPI StartReadData(LPVOID lpParam)
	{
		CSocketClient* p = (CSocketClient*)lpParam;
		int len = 0;
		char* buf = p->GetRecvBuf(&len);
		while (true)
		{
			memset(buf, 0, len);
			int recvLen = recv(p->GetServerSocket(), buf, len, 0);
			if (recvLen > 0)
			{
				p->OnRecvData((BYTE*)buf, recvLen);
			}
		}
		return 0;
	}

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

	void CSocketClient::CleanThread()
	{
		if (m_readThreadInfo.hThread > 0)
		{
			::TerminateThread(m_readThreadInfo.hThread, 0);
			::CloseHandle(m_readThreadInfo.hThread);
			m_readThreadInfo = { 0 };
		}
		if (m_notifyThreadInfo.hThread > 0)
		{
			::TerminateThread(m_notifyThreadInfo.hThread, 0);
			::CloseHandle(m_notifyThreadInfo.hThread);
			m_notifyThreadInfo = { 0 };
		}
	}

	void CSocketClient::Dispose()
	{
		CleanSocket();
		CleanThread();
	}

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

	bool CSocketClient::IsInited()
	{
		return m_bInited;
	}

	char* CSocketClient::GetRecvBuf(int *len)
	{
		*len = m_nSocketBufLen;
		return m_pRecvBuf;
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

	DWORD WINAPI NotifyCallerMsg(LPVOID lpParam)
	{
		CSocketClient* p = (CSocketClient*)lpParam;
		while (true)
		{
			p->NotifyMsg();
		}
		return 0;
	}

	void CSocketClient::NotifyMsg()
	{
		if (m_msg.haveMsg)
		{
			m_lpfnNotifyMsg(m_msg.type, m_msg.msg);
			m_msg.haveMsg = false;
		}
	}

	void CSocketClient::SetNotifyMsg(SocketClientMsgType type, TCHAR* msg)
	{
		m_msg.type = type;
		memset(m_msg.msg, 0, m_msgbufsize);
		if (msg != NULL)
		{
			int n = GetStrByteCount(msg);
			memcpy(m_msg.msg, msg, n);
		}
		m_msg.haveMsg = true;
	}
}