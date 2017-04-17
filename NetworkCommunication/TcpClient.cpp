#include "stdafx.h"
#include "TcpClient.h"
#include "NetTool.h"
#include "StringHandle.h"

namespace NetworkCommunication
{
	//接收tcp数据线程入口
	DWORD WINAPI OnRecvTcpData(LPVOID lpParam);

	//读取tcp数据线程入口
	DWORD WINAPI ReadTcpData(LPVOID lpParam);

	//连接服务端线程入口
	DWORD WINAPI ConnectServer(LPVOID lpParam);

	//超时线程入口
	DWORD WINAPI Timeout(LPVOID lpParam);

	//接收数据线程入口参数
	typedef struct tagRecvDataThreadEntryPara
	{
		CTcpClient* pClient;//客户端指针
		BYTE* buf;//缓冲区
		int nlen;//缓冲区长度
	}RecvDataThreadEntryPara, *LPRecvDataThreadEntryPara;

	//超时线程入口参数
	typedef struct tagTimeoutThreadEntryPara
	{
		CTcpClient* pClient;//客户端指针
		int nTimeout;
	}TimeoutThreadEntryPara, *LPTimeoutThreadEntryPara;

	CTcpClient::CTcpClient() :
		m_nRecvTcpBufLen(0),
		m_pRecvTcpBuf(NULL),
		m_strServerIP(NULL),
		m_nServerPort(0),
		m_bIsCleaned(false),
		m_socket(0),
		m_addrSrv({ 0 }),
		m_lpfnOnRecvNotifyEvt(NULL),
		m_bHaslpfnRecvTcpData(false),
		m_nReconnectTimeSpan(3000),
		m_nReconnectTimes(0),
		m_nReconnected(0),
		m_bReconnecting(false),
		m_bAutoReconnect(true),
		m_bExitThread(false),
		m_nConnectTimeout(2 * 1000),
		m_tiConnect({ 0 }),
		m_tiConnectTimeout({ 0 }),
		m_bConnectedTimeout(false)
	{

	}

	CTcpClient::~CTcpClient()
	{
		m_bExitThread = true;
		CleanSocket();
		if (m_pRecvTcpBuf)
		{
			delete m_pRecvTcpBuf;
			m_pRecvTcpBuf = NULL;
		}
	}

	void CTcpClient::Init(const TCHAR* ip, int port, LPOnRecvNotifyEvt lpfnOnRecvNotifyEvt, int socketBufLen, bool autoReconnect,
		int reconnectTimes, int reconnectTimeSpan, int connectTimeout)
	{
		if (!m_bInited)
		{
			m_bAutoReconnect = autoReconnect;
			m_nReconnectTimes = reconnectTimes;
			m_nReconnectTimeSpan = reconnectTimeSpan;
			m_bInited = true;
			m_nRecvTcpBufLen = socketBufLen;
			m_pRecvTcpBuf = new char[socketBufLen];
			m_strServerIP = ip;
			m_nServerPort = port;
			m_lpfnOnRecvNotifyEvt = lpfnOnRecvNotifyEvt;
			m_nConnectTimeout = connectTimeout;
			InitSocket();
		}
	}

	void CTcpClient::SetCallback(LPOnRecvTcpData lpfnOnRecvTcpData)
	{
		m_bHaslpfnRecvTcpData = true;
		m_lpfnOnRecvTcpData = lpfnOnRecvTcpData;
	}

	void CTcpClient::InitSocket()
	{
		WSADATA wsaData;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			SendNotifyEvt(TcpClientEvtType::error, _T("Socket初始化失败!\n"));
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
			SendNotifyEvt(TcpClientEvtType::error, _T("创建Socket失败!\n"));
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
		if (m_bReconnecting || m_bExitThread == false)
		{
			if (m_nConnectTimeout > 0)//连接超时时间不为0时，启动超时线程
			{
				m_bConnectedTimeout = true;//指示连接已超时
				m_tiConnectTimeout.hThread = ::CreateThread(NULL, 0, Timeout, this, NULL, &(m_tiConnectTimeout.dwThreadID));
			}
			int result = connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
			if (m_nConnectTimeout > 0)
			{
				m_bConnectedTimeout = false;//指示已连接上,没有超时
			}
			if (result == SOCKET_ERROR)
			{
				TCHAR msg[100];
				wsprintf(msg, _T("failed to connect server: %s:%d\n"), m_strServerIP, m_nServerPort);
				SendNotifyEvt(TcpClientEvtType::disconnected, msg);
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
			m_tiConnect.hThread = ::CreateThread(NULL, 0, NetworkCommunication::ConnectServer, this, NULL, &(m_tiConnect.dwThreadID));
		}
	}

	void CTcpClient::OnLoseConnect(LoseConnectReason reason)
	{
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
		TCHAR msg[100];
		wsprintf(msg, _T("success to connect server: %s:%d\n"), m_strServerIP, m_nServerPort);
		SendNotifyEvt(TcpClientEvtType::connected, msg);
		::CreateThread(NULL, 0, NetworkCommunication::ReadTcpData, this, NULL, NULL);
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
		CloseConnect();
		ReconnectServer();
	}

	void CTcpClient::CloseConnect()
	{
		m_bReconnecting = false;
		m_bExitThread = true;
		closesocket(m_socket);
		if (m_tiConnect.hThread)
		{
			::TerminateThread(m_tiConnect.hThread, 0);
			m_tiConnect = { 0 };
		}
		if (m_tiConnectTimeout.hThread)
		{
			::TerminateThread(m_tiConnectTimeout.hThread, 0);
			m_tiConnectTimeout = { 0 };
		}
		m_bExitThread = false;
	}

	SOCKET CTcpClient::GetClientSocket()
	{
		return m_socket;
	}

	DWORD WINAPI ReadTcpData(LPVOID lpParam)
	{
		CTcpClient* p = (CTcpClient*)lpParam;
		while (true)
		{
			if (p->ReadTcpData())
			{
				break;
			}
		}
		return 0;
	}

	bool CTcpClient::ReadTcpData()
	{
		memset(m_pRecvTcpBuf, 0, m_nRecvTcpBufLen);
		int len = recv(m_socket, m_pRecvTcpBuf, m_nRecvTcpBufLen, 0);
		if (m_bExitThread)
		{
			return true;
		}
		if (len > 0 && m_bHaslpfnRecvTcpData)
		{
			BYTE* buf = new BYTE[len];
			memcpy(buf, m_pRecvTcpBuf, len);
			LPRecvDataThreadEntryPara info = new RecvDataThreadEntryPara{ this, buf, len };
			::CreateThread(NULL, 0, NetworkCommunication::OnRecvTcpData, info, NULL, NULL);
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

	void CTcpClient::SendNotifyEvt(TcpClientEvtType type, TCHAR* msg)
	{
		if (m_lpfnOnRecvNotifyEvt)
		{
			if (!m_lpfnOnRecvNotifyEvt(type, msg))
			{
				if (type == error || type == Debug || type == TcpClientEvtType::Info)
				{
					Printf(msg);
				}
			}
		}
	}

	void CTcpClient::Printf(TCHAR* msg)
	{
#ifdef _DEBUG
#ifdef _CONSOLE_APP
		_tprintf(msg);
#endif
#ifdef _WINDOWS_
		OutputDebugString(msg);
#endif
#endif // _DEBUG
	}

	void CTcpClient::SimulateServerData(BYTE* buf, int len)
	{
		BYTE* buf1 = new BYTE[len];
		memcpy(buf1, buf, len);
		OnRecvTcpData(buf1, len);
	}

	DWORD WINAPI OnRecvTcpData(LPVOID lpParam)
	{
		LPRecvDataThreadEntryPara p = (LPRecvDataThreadEntryPara)lpParam;
		p->pClient->OnRecvTcpData(p->buf, p->nlen);
		delete p;
		return 0;
	}

	void CTcpClient::OnRecvTcpData(BYTE buf[], int len)
	{
		if (m_lpfnOnRecvTcpData&&buf&&len > 0)
		{
			if (!m_lpfnOnRecvTcpData(buf, len))
			{
				delete buf;
			}
		}
		else
		{
			delete buf;
		}
	}

	DWORD WINAPI Timeout(LPVOID lpParam)
	{
		CTcpClient* p = (CTcpClient*)lpParam;
		p->OnConnectTimeout();
		return 0;
	}

	void CTcpClient::OnConnectTimeout()
	{
		Sleep(m_nConnectTimeout);

		m_tiConnectTimeout = { 0 };//重置连接超时线程信息

		if (m_bExitThread)//指示应该退出线程
		{
			return;
		}

		if (m_bConnectedTimeout)//指示连接已超时,可以进行超时处理
		{
			if (m_tiConnect.hThread)
			{
				::TerminateThread(m_tiConnect.hThread, 0);
				m_tiConnect = { 0 };
			}

			bool connect = false;//是否应该重新启动连接
			TCHAR msg[100];
			wsprintf(msg, _T("failed to connect server(time out): %s:%d\n"), m_strServerIP, m_nServerPort);
			SendNotifyEvt(TcpClientEvtType::disconnected, msg);
			if (m_nReconnectTimes > 0)//有限次数重连
			{
				m_nReconnected++;
				if (m_nReconnected == m_nReconnectTimes)//已达到重连次数
				{
					m_nReconnected = 0;//充值重连次数
					m_bReconnecting = false;//取消正在重连
				}
				else
				{
					connect = true;
				}
			}
			else//无限制重连
			{
				connect = true;
			}
			if (connect)
			{
				//开始重连
				m_tiConnect.hThread = ::CreateThread(NULL, 0, NetworkCommunication::ConnectServer, this, NULL, &(m_tiConnect.dwThreadID));
			}
		}
	}
}