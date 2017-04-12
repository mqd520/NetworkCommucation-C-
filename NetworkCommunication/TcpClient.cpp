#include "stdafx.h"
#include "TcpClient.h"
#include "NetTool.h"
#include "StringHandle.h"

namespace NetworkCommunication
{
	//接收socket数据线程入口
	DWORD WINAPI OnRecvSocketData(LPVOID lpParam);

	//读取socket数据线程入口
	DWORD WINAPI ReadSocketData(LPVOID lpParam);

	//连接服务端线程入口
	DWORD WINAPI ConnectServer(LPVOID lpParam);

	//线程入口参数
	typedef struct tagThreadEntryPara
	{
		CTcpClient* pClient;//客户端指针
		BYTE* buf;//缓冲区
		int len;//缓冲区长度
	}ThreadEntryPara, *LPThreadEntryPara;

	CTcpClient::CTcpClient() :
		m_nRecvSocketBufLen(0),
		m_pRecvSocketBuf(NULL),
		m_strServerIP(NULL),
		m_nServerPort(0),
		m_bIsCleaned(false),
		m_socket(0),
		m_addrSrv({ 0 }),
		m_lpfnOnRecvNotifyEvt(NULL),
		m_bHaslpfnRecvSocketData(false),
		m_bConnected(false),
		m_nReconnectTimeSpan(3000),
		m_nReconnectTimes(0),
		m_nReconnected(0),
		m_bReconnecting(false),
		m_bAutoReconnect(true),
		m_bExitThread(false)
	{

	}

	CTcpClient::~CTcpClient()
	{
		m_bExitThread = true;
		CleanSocket();
		if (m_pRecvSocketBuf)
		{
			delete m_pRecvSocketBuf;
			m_pRecvSocketBuf = NULL;
		}
	}

	void CTcpClient::Init(const TCHAR* ip, int port, LPOnRecvNotifyEvt lpfnOnRecvNotifyEvt, int socketBufLen, bool autoReconnect,
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
		}
	}

	void CTcpClient::SetCallback(LPOnRecvSocketData lpfnOnRecvSocketData)
	{
		m_bHaslpfnRecvSocketData = true;
		m_lpfnOnRecvSocketData = lpfnOnRecvSocketData;
	}

	void CTcpClient::InitSocket()
	{
		WSADATA wsaData;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			SendNotifyEvt(SocketClientEvtType::error, _T("Socket初始化失败!\n"));
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

	void CTcpClient::CreateClientSocket()
	{
		m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_socket == INVALID_SOCKET)
		{
			SendNotifyEvt(SocketClientEvtType::error, _T("创建Socket失败!\n"));
		}
	}

	DWORD WINAPI ConnectServer(LPVOID lpParam)
	{
		CTcpClient* p = (CTcpClient*)lpParam;
		while (true)
		{
			if (p->ConnectServer())
			{
				break;
			}
		}
		return 0;
	}

	bool CTcpClient::ConnectServer()
	{
		if (m_bConnected == false || m_bReconnecting || m_bExitThread == false)
		{
			int result = connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
			if (result == SOCKET_ERROR)
			{
				TCHAR msg[100];
				wsprintf(msg, _T("failed to connect server: %s:%d\n"), m_strServerIP, m_nServerPort);
				SendNotifyEvt(SocketClientEvtType::error, msg);
				if (m_nReconnectTimes > 0)
				{
					m_nReconnected++;
					if (m_nReconnected == m_nReconnectTimes)
					{
						m_nReconnected = 0;
						m_bReconnecting = false;
					}
				}
				::Sleep(m_nReconnectTimeSpan);
				return false;
			}
			else
			{
				OnConnected();
				return true;
			}
		}
		else
		{
			return true;
		}
	}

	void CTcpClient::ReconnectServer()
	{
		if (!m_bReconnecting)
		{
			m_bReconnecting = true;
			CreateClientSocket();
			::CreateThread(NULL, 0, NetworkCommunication::ConnectServer, this, NULL, NULL);
		}
	}

	void CTcpClient::OnLoseConnect(LoseConnectReason reason)
	{
		m_bConnected = false;
		if (reason == LoseConnectReason::Client)
		{
			SendNotifyEvt(disconnected, _T("client disconnect the connection!\n"));
		}
		else
		{
			if (reason == LoseConnectReason::Server)
			{
				SendNotifyEvt(disconnected, _T("server disconnect the connection!\n"));
			}
			else if (reason == LoseConnectReason::Net)
			{
				SendNotifyEvt(disconnected, _T("Net trouble happended!\n"));
			}
			if (m_bExitThread == false && m_bAutoReconnect)
			{
				ReconnectServer();
			}
		}
	}

	void CTcpClient::OnConnected()
	{
		m_nReconnected = 0;
		m_bReconnecting = false;
		m_bConnected = true;
		TCHAR msg[100];
		wsprintf(msg, _T("success to connect server: %s:%d\n"), m_strServerIP, m_nServerPort);
		SendNotifyEvt(SocketClientEvtType::connected, msg);
		::CreateThread(NULL, 0, NetworkCommunication::ReadSocketData, this, NULL, NULL);
	}

	void CTcpClient::CleanSocket()
	{
		if (!m_bIsCleaned)
		{
			CloseConnect();
			WSACleanup();
			m_bIsCleaned = true;
		}
	}

	void CTcpClient::Connect()
	{
		if (!m_bConnected)
		{
			ReconnectServer();
		}
	}

	void CTcpClient::Reconnect()
	{
		ReconnectServer();
	}

	void CTcpClient::CloseConnect()
	{
		m_bReconnecting = false;
		m_bConnected = false;
		closesocket(m_socket);
	}

	SOCKET CTcpClient::GetClientSocket()
	{
		return m_socket;
	}

	DWORD WINAPI ReadSocketData(LPVOID lpParam)
	{
		CTcpClient* p = (CTcpClient*)lpParam;
		while (true)
		{
			if (p->ReadSocketData())
			{
				break;
			}
		}
		return 0;
	}

	bool CTcpClient::ReadSocketData()
	{
		memset(m_pRecvSocketBuf, 0, m_nRecvSocketBufLen);
		int len = recv(m_socket, m_pRecvSocketBuf, m_nRecvSocketBufLen, 0);
		if (m_bExitThread)
		{
			return true;
		}
		if (len > 0 && m_bHaslpfnRecvSocketData)
		{
			BYTE* buf = new BYTE[len];
			memcpy(buf, m_pRecvSocketBuf, len);
			LPThreadEntryPara info = new ThreadEntryPara{ this, buf, len };
			::CreateThread(NULL, 0, NetworkCommunication::OnRecvSocketData, info, NULL, NULL);
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
			return true;
		}
		return false;
	}

	bool CTcpClient::GetConnectStatus()
	{
		return m_bConnected;
	}

	bool CTcpClient::SendData(BYTE buf[], int len)
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

	void CTcpClient::SendNotifyEvt(SocketClientEvtType type, TCHAR* msg)
	{
		if (m_lpfnOnRecvNotifyEvt)
		{
			if (!m_lpfnOnRecvNotifyEvt(type, msg))
			{
				if (type == error || type == Debug || type == SocketClientEvtType::Info)
				{
					Printf(msg);
				}
			}
		}
	}

	void CTcpClient::Printf(TCHAR* msg)
	{
#ifdef _DEBUG
#ifdef _CONSOLE
		_tprintf(msg);
#endif
#ifdef _WINDOWS
		TRACE(msg);
#endif
#ifdef _MFCDLL
		TRACE(msg);
#endif
#endif // _DEBUG
	}

	void CTcpClient::SimulateServerData(BYTE* buf, int len)
	{
		OnRecvSocketData(buf, len);
	}

	DWORD WINAPI OnRecvSocketData(LPVOID lpParam)
	{
		LPThreadEntryPara p = (LPThreadEntryPara)lpParam;
		p->pClient->OnRecvSocketData(p->buf, p->len);
		delete p;
		return 0;
	}

	void CTcpClient::OnRecvSocketData(BYTE buf[], int len)
	{
		if (m_lpfnOnRecvSocketData&&buf&&len > 0)
		{
			if (!m_lpfnOnRecvSocketData(buf, len))
			{
				delete buf;
			}
		}
		else
		{
			delete buf;
		}
	}
}