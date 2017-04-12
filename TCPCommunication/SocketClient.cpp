#include "stdafx.h"
#include "SocketClient.h"
#include "NetTool.h"
#include "StringHandle.h"

namespace TCPCommunication
{
	//读取Socket数据线程入口
	DWORD WINAPI ReadSocketData(LPVOID lpParam);

	//读取缓存Socket数据线程入口
	DWORD WINAPI ReadCatchSocketData(LPVOID lpParam);

	//通知消息线程入口
	DWORD WINAPI ReadNotifyEvt(LPVOID lpParam);

	//连接服务端线程入口
	DWORD WINAPI ConnectServer(LPVOID lpParam);

	CSocketClient::CSocketClient() :
		m_nRecvSocketBufLen(0),
		m_pRecvSocketBuf(NULL),
		m_strServerIP(NULL),
		m_nServerPort(0),
		m_bIsCleaned(false),
		m_socket(0),
		m_strClientIP(NULL),
		m_nClientPort(0),
		m_addrSrv({ 0 }),
		m_tiReadSocketData({ 0, 0, true }),
		m_tiReadNotifyEvt({ 0 }),
		m_evt({ false, SocketClientEvtType::Info, new TCHAR[1024] }),
		m_lpfnOnRecvNotifyEvt(NULL),
		m_tiReadCatchSocketData({ 0 }),
		m_bHaslpfnRecvSocketData(false),
		m_tiConnectServer({ 0, 0, true }),
		m_bConnected(false),
		m_nReconnectTimeSpan(3000),
		m_nReconnectTimes(3),
		m_nReconnected(0),
		m_bReconnecting(false),
		m_bAutoReconnect(true),
		m_whileinfo({ false, false, false, true })
	{

	}

	CSocketClient::~CSocketClient()
	{
		if (m_pRecvSocketBuf)
		{
			delete m_pRecvSocketBuf;
			m_pRecvSocketBuf = NULL;
		}
		if (m_evt.msg)
		{
			delete m_evt.msg;
		}
		Dispose();
	}

	void CSocketClient::Init(const TCHAR* ip, int port, LPOnRecvNotifyEvt lpfnOnRecvNotifyEvt, int socketBufLen, bool autoReconnect,
		int reconnectTimes, int reconnectTimeSpan)
	{
		if (!m_bInited)
		{
			m_bAutoReconnect = autoReconnect;
			m_nReconnectTimes = reconnectTimes;
			m_nReconnectTimeSpan = reconnectTimeSpan;
			m_bInited = true;
			m_nRecvSocketBufLen = socketBufLen;
			m_pRecvSocketBuf = new char[socketBufLen];
			m_strServerIP = ip;
			m_nServerPort = port;
			m_lpfnOnRecvNotifyEvt = lpfnOnRecvNotifyEvt;
			InitSocket();
			if (m_lpfnOnRecvNotifyEvt)
			{
				m_tiReadNotifyEvt.hThread = ::CreateThread(NULL, 0, TCPCommunication::ReadNotifyEvt, this, NULL, &m_tiReadNotifyEvt.nThreadID);
			}
		}
	}

	void CSocketClient::SetCallback(LPOnRecvSocketData lpfnOnRecvSocketData)
	{
		m_bHaslpfnRecvSocketData = true;
		m_lpfnOnRecvSocketData = lpfnOnRecvSocketData;
	}

	void CSocketClient::InitSocket()
	{
		WSADATA wsaData;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			SaveNotifyEvt(SocketClientEvtType::error, _T("Socket初始化失败!\n"));
		}
		else
		{
			m_addrSrv.sin_family = AF_INET;
			m_addrSrv.sin_port = htons(m_nServerPort);
#ifdef _UNICODE
			string strTmp = UTF8ToMultiByte(m_strServerIP);
			m_addrSrv.sin_addr.S_un.S_addr = inet_addr(strTmp.c_str());
#else
			m_addrSrv.sin_addr.S_un.S_addr = inet_addr(m_strServerIP);
#endif
		}
	}

	void CSocketClient::CreateClientSocket()
	{
		m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_socket == INVALID_SOCKET)
		{
			SaveNotifyEvt(SocketClientEvtType::error, _T("创建Socket失败!\n"));
		}
	}

	DWORD WINAPI ConnectServer(LPVOID lpParam)
	{
		CSocketClient* p = (CSocketClient*)lpParam;
		while (true)
		{
			if (p->GetWhileInfo().bConnectServer)
			{
				p->ConnectServer();
			}
		}
	}

	void CSocketClient::ConnectServer()
	{
		if (m_bConnected == false)
		{
			int result = connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
			if (result == SOCKET_ERROR)
			{
				m_whileinfo.bReadSocketData = false;
				m_whileinfo.bReadCatchSocketData = false;
				TCHAR msg[100];
				wsprintf(msg, _T("failed to connect server: %s:%d\n"), m_strServerIP, m_nServerPort);
				SaveNotifyEvt(SocketClientEvtType::disconnected, msg);
				if (m_nReconnectTimes > 0)
				{
					m_nReconnected++;
					if (m_nReconnected == m_nReconnectTimes)
					{
						m_nReconnected = 0;
						m_bReconnecting = false;
						m_whileinfo.bConnectServer = false;
					}
				}
				::Sleep(m_nReconnectTimeSpan);
			}
			else
			{
				OnConnected();
			}
		}
	}

	void CSocketClient::ReconnectServer()
	{
		if (!m_bReconnecting)
		{
			m_bReconnecting = true;
			CreateClientSocket();
			m_whileinfo.bConnectServer = true;
		}
	}

	void CSocketClient::OnLoseConnect(LoseConnectReason reason)
	{
		m_bConnected = false;
		m_whileinfo.bReadSocketData = false;
		m_whileinfo.bReadCatchSocketData = false;
		if (reason == LoseConnectReason::Client)
		{
			SaveNotifyEvt(disconnected, _T("client disconnect the connection!\n"));
		}
		else
		{
			if (reason == LoseConnectReason::Server)
			{
				SaveNotifyEvt(disconnected, _T("server disconnect the connection!\n"));
			}
			else if (reason == LoseConnectReason::Net)
			{
				SaveNotifyEvt(disconnected, _T("Net trouble happended!\n"));
			}
			if (m_bAutoReconnect)
			{
				ReconnectServer();
			}
		}
	}

	void CSocketClient::OnConnected()
	{
		m_nReconnected = 0;
		m_bReconnecting = false;
		m_bConnected = true;
		m_whileinfo.bConnectServer = false;
		m_whileinfo.bReadSocketData = true;
		m_whileinfo.bReadCatchSocketData = true;
		TCHAR msg[100];
		wsprintf(msg, _T("success to connect server: %s:%d\n"), m_strServerIP, m_nServerPort);
		SaveNotifyEvt(SocketClientEvtType::connected, msg);
	}

	void CSocketClient::PauseThread(bool pause, LPThreadInfo ti)
	{
		if (pause)
		{
			if (ti->bPause == false)
			{
				::SuspendThread(ti->hThread);
				ti->bPause = true;
			}
		}
		else
		{
			if (ti->bPause == true)
			{
				::ResumeThread(ti->hThread);
				ti->bPause = false;
			}
		}
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

	void CSocketClient::Connect()
	{
		if (m_tiReadSocketData.nThreadID == 0)
		{
			CreateThread();
			ReconnectServer();
		}
	}

	void CSocketClient::Reconnect()
	{
		ReconnectServer();
	}

	void CSocketClient::CreateThread()
	{
		m_tiReadSocketData.hThread = ::CreateThread(NULL, 0, TCPCommunication::ReadSocketData, this, NULL, &m_tiReadSocketData.nThreadID);
		m_tiReadCatchSocketData.hThread = ::CreateThread(NULL, 0, TCPCommunication::ReadCatchSocketData, this, NULL, &m_tiReadCatchSocketData.nThreadID);
		m_tiConnectServer.hThread = ::CreateThread(NULL, 0, TCPCommunication::ConnectServer, this, NULL, &m_tiConnectServer.nThreadID);
	}

	void CSocketClient::CloseConnect()
	{
		closesocket(m_socket);
	}

	SOCKET CSocketClient::GetClientSocket()
	{
		return m_socket;
	}

	DWORD WINAPI ReadSocketData(LPVOID lpParam)
	{
		CSocketClient* p = (CSocketClient*)lpParam;
		while (true)
		{
			if (p->GetWhileInfo().bReadSocketData)
			{
				p->ReadSocketData();
			}
		}
		return 0;
	}

	void CSocketClient::ReadSocketData()
	{
		memset(m_pRecvSocketBuf, 0, m_nRecvSocketBufLen);
		int len = recv(m_socket, m_pRecvSocketBuf, m_nRecvSocketBufLen, 0);
		if (len > 0 && m_bHaslpfnRecvSocketData)
		{
			BYTE* buf = new BYTE[len];
			memcpy(buf, m_pRecvSocketBuf, len);
			m_vecCatchRecvSocketBuf.push_back({ (int)buf, len });
		}
		else
		{
			if (len == 0)//服务端主动断开连接
			{
				OnLoseConnect(LoseConnectReason::Server);
			}
			else if (len == -1)//网络故障
			{
				OnLoseConnect(LoseConnectReason::Net);
			}
		}
	}

	void CSocketClient::CleanThread()
	{
		if (m_tiReadSocketData.hThread > 0)
		{
			::TerminateThread(m_tiReadSocketData.hThread, 0);
			::CloseHandle(m_tiReadSocketData.hThread);
			m_tiReadSocketData = { 0 };
		}
		if (m_tiReadNotifyEvt.hThread > 0)
		{
			::TerminateThread(m_tiReadNotifyEvt.hThread, 0);
			::CloseHandle(m_tiReadNotifyEvt.hThread);
			m_tiReadNotifyEvt = { 0 };
		}
		if (m_tiReadCatchSocketData.hThread > 0)
		{
			::TerminateThread(m_tiReadCatchSocketData.hThread, 0);
			::CloseHandle(m_tiReadCatchSocketData.hThread);
			m_tiReadCatchSocketData = { 0 };
		}
		if (m_tiConnectServer.hThread > 0)
		{
			::TerminateThread(m_tiConnectServer.hThread, 0);
			::CloseHandle(m_tiConnectServer.hThread);
			m_tiConnectServer = { 0 };
		}
	}

	void CSocketClient::Dispose()
	{
		CleanSocket();
		CleanThread();
	}

	bool CSocketClient::GetConnectStatus()
	{
		return m_bConnected;
	}

	bool CSocketClient::SendData(BYTE buf[], int len)
	{
		bool b = false;
		int sended = 0;
		while (true)
		{
			int result = send(m_socket, (char*)buf, len - sended, 0);
			if (result == SOCKET_ERROR)
			{
				break;
			}
			else
			{
				sended += result;
				if (sended == len)
				{
					b = true;
					break;
				}
			}
		}
		return b;
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

	DWORD WINAPI ReadNotifyEvt(LPVOID lpParam)
	{
		CSocketClient* p = (CSocketClient*)lpParam;
		while (true)
		{
			if (p->GetWhileInfo().bReadNotifyEvt)
			{
				p->ReadNotifyEvt();
			}
		}
		return 0;
	}

	void CSocketClient::ReadNotifyEvt()
	{
		if (m_evt.haveMsg)
		{
			if (m_lpfnOnRecvNotifyEvt)
			{
				bool b = m_lpfnOnRecvNotifyEvt(m_evt.type, m_evt.msg);
				if (b&&m_evt.msg[0] != 0)
				{
					Printf(m_evt.msg);
				}
			}
			m_evt.haveMsg = false;
		}
	}

	void CSocketClient::SaveNotifyEvt(SocketClientEvtType type, TCHAR* msg)
	{
		m_evt.type = type;
		memset(m_evt.msg, 0, m_msgbufsize);
		if (msg != NULL)
		{
			int n = GetStrByteCount(msg);
			memcpy(m_evt.msg, msg, n);
		}
		m_evt.haveMsg = true;
	}

	DWORD WINAPI ReadCatchSocketData(LPVOID lpParam)
	{
		CSocketClient* p = (CSocketClient*)lpParam;
		while (true)
		{
			if (p->GetWhileInfo().bReadCatchSocketData)
			{
				p->ReadCatchSocketData();
			}
		}
		return 0;
	}

	void CSocketClient::ReadCatchSocketData()
	{
		if (m_vecCatchRecvSocketBuf.size() > 0)
		{
			BYTE* buf = (BYTE*)(m_vecCatchRecvSocketBuf[0].adress);
			int len = m_vecCatchRecvSocketBuf[0].len;
			m_vecCatchRecvSocketBuf.erase(m_vecCatchRecvSocketBuf.begin());
			if (m_bHaslpfnRecvSocketData && buf)
			{
				if (!SendRecvData(buf, len))
				{
					delete buf;
				}
			}
		}
	}

	void CSocketClient::Printf(TCHAR* msg)
	{
#ifdef _DEBUG
#ifdef _CONSOLE
		_tprintf(msg);
#endif
#ifdef _WINDOWS
		TRACE(msg);
#endif
#endif // _DEBUG
	}

	bool CSocketClient::SendRecvData(BYTE buf[], int len)
	{
		return m_lpfnOnRecvSocketData(buf, len);
	}

	ThreadWhileInfo CSocketClient::GetWhileInfo()
	{
		return m_whileinfo;
	}

	void CSocketClient::SimulateServerData(BYTE* buf, int len)
	{
		m_vecCatchRecvSocketBuf.push_back({ (int)&buf, len });
	}
}