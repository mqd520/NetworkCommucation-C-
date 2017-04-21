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
	//DWORD WINAPI ConnectServer(LPVOID lpParam);

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
		m_lpfnOnRecvTcpEvt(NULL),
		m_bHaslpfnRecvTcpData(false),
		m_nReconnectTimeSpan(3000),
		m_nAllowReconnectCount(0),
		m_nReconnectCount(0),
		m_bReconnecting(false),
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
		CloseConnect();
		if (m_pRecvTcpBuf)
		{
			delete m_pRecvTcpBuf;
			m_pRecvTcpBuf = NULL;
		}
	}

	void CTcpClient::Init(const TCHAR* ip, int port, int socketBufLen, int allowReconnectCount, int reconnectTimeSpan, int connectTimeout)
	{
		if (!m_bInited)
		{
			m_nAllowReconnectCount = allowReconnectCount;
			m_nReconnectTimeSpan = reconnectTimeSpan;
			m_bInited = true;
			m_nRecvTcpBufLen = socketBufLen;
			m_pRecvTcpBuf = new char[socketBufLen];
			m_strServerIP = ip;
			m_nServerPort = port;
			m_nConnectTimeout = connectTimeout;
			InitSocket();
			InitServerAddr();
		}
	}

	void CTcpClient::SetCallback(LPOnRecvTcpData lpfnOnRecvTcpData, LPOnRecvTcpEvt lpfnOnRecvTcpEvt)
	{
		m_bHaslpfnRecvTcpData = true;
		m_lpfnOnRecvTcpData = lpfnOnRecvTcpData;
		m_lpfnOnRecvTcpEvt = lpfnOnRecvTcpEvt;
	}

	void CTcpClient::InitSocket()
	{
		WSADATA wsaData;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			SendTcpEvt(TcpEvtType::error, _T("Socket初始化失败!\n"));
		}
	}

	void CTcpClient::CreateSocket()
	{
		m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_socket == INVALID_SOCKET)
		{
			SendTcpEvt(TcpEvtType::error, _T("创建Socket失败!\n"));
		}
	}

	//DWORD WINAPI ConnectServer(LPVOID lpParam)
	//{
	//	CTcpClient* p = (CTcpClient*)lpParam;
	//	while (true)
	//	{
	//		if (p->ConnectServer())
	//		{
	//			break;
	//		}
	//	}
	//	return 0;
	//}

	//bool CTcpClient::ConnectServer()
	//{
	//	if (m_bReconnecting || m_bExitThread == false)
	//	{
	//		if (m_nConnectTimeout > 0)//连接超时时间不为0时，启动超时线程
	//		{
	//			m_bConnectedTimeout = true;//指示连接已超时
	//			m_tiConnectTimeout.hThread = ::CreateThread(NULL, 0, Timeout, this, NULL, &(m_tiConnectTimeout.dwThreadID));
	//		}
	//		int result = connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
	//		if (m_nConnectTimeout > 0)
	//		{
	//			m_bConnectedTimeout = false;//指示已连接上,没有超时
	//		}
	//		if (result == SOCKET_ERROR)
	//		{
	//			TCHAR msg[100];
	//			wsprintf(msg, _T("failed to connect server: %s:%d\n"), m_strServerIP, m_nServerPort);
	//			SendTcpEvt(TcpEvtType::disconnected, msg);
	//			if (m_nAllowReconnectCount > 0)
	//			{
	//				m_nReconnectCount++;
	//				if (m_nReconnectCount == m_nAllowReconnectCount)
	//				{
	//					m_nReconnectCount = 0;
	//					m_bReconnecting = false;
	//				}
	//			}
	//			::Sleep(m_nReconnectTimeSpan);
	//			return false;
	//		}
	//		else
	//		{
	//			OnConnectSuccess();
	//			return true;
	//		}
	//	}
	//	else
	//	{
	//		return true;
	//	}
	//}

	//void CTcpClient::ReconnectServer()
	//{
	//	if (!m_bReconnecting)
	//	{
	//		m_bReconnecting = true;
	//		CreateSocket();
	//		m_tiConnect.hThread = ::CreateThread(NULL, 0, NetworkCommunication::ConnectServer, this, NULL, &(m_tiConnect.dwThreadID));
	//	}
	//}

	void CTcpClient::OnLoseConnect(LoseConnectReason reason)
	{
		if (reason == LoseConnectReason::Client)
		{
			SendTcpEvt(disconnected, _T("client disconnect the connection!\n"));
		}
		else
		{
			if (reason == LoseConnectReason::Server)
			{
				SendTcpEvt(disconnected, _T("server disconnect the connection!\n"));
			}
			else if (reason == LoseConnectReason::Net)
			{
				SendTcpEvt(disconnected, _T("Net trouble happended!\n"));
			}
			if (m_bExitThread == false)
			{
				Connect();
				PauseThread(&m_tiReadTcpData, true);
			}
		}
	}

	void CTcpClient::OnConnectSuccess()
	{
		m_nReconnectCount = 0;
		m_bReconnecting = false;
		TCHAR msg[100];
		wsprintf(msg, _T("success to connect server: %s:%d\n"), m_strServerIP, m_nServerPort);
		SendTcpEvt(TcpEvtType::connected, msg);
		if (m_tiReadTcpData.hThread == 0)//启动读取tcp数据线程
		{
			m_tiReadTcpData.hThread = ::CreateThread(NULL, 0, NetworkCommunication::ReadTcpData, this, NULL, &m_tiReadTcpData.dwThreadID);
		}
		else
		{
			PauseThread(&m_tiReadTcpData, false);//恢复读取tcp数据线程
		}
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
		CloseConnect();//关闭可能已经存在的连接
		CreateSocket();//重新创建客户端socket
		if (m_tiConnect.hThread == 0)
		{
			//启动连接服务端线程
			m_tiConnect.hThread = ::CreateThread(NULL, 0, NetworkCommunication::ConnectServer, this, NULL, &m_tiConnect.dwThreadID);
		}
		else
		{
			//恢复已挂起的连接线程
			m_nReconnectCount = 0;
			PauseThread(&m_tiConnect, false);
		}
	}

	void CTcpClient::CloseConnect()
	{
		m_bReconnecting = false;
		m_bExitThread = true;
		closesocket(m_socket);
		PauseThread(&m_tiConnect, true);
		m_bExitThread = false;
	}

	SOCKET CTcpClient::GetClientSocket()
	{
		return m_socket;
	}

	DWORD WINAPI ReadTcpData(LPVOID lpParam)
	{
		CTcpClient* p = (CTcpClient*)lpParam;
		p->ReadTcpData();
		return 0;
	}

	void CTcpClient::ReadTcpData()
	{
		while (true)
		{
			memset(m_pRecvTcpBuf, 0, m_nRecvTcpBufLen);
			int len = recv(m_socket, m_pRecvTcpBuf, m_nRecvTcpBufLen, 0);
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
			}
		}
	}

	bool CTcpClient::SendData(BYTE buf[], int len, int* actualLen)
	{
		bool b = false;
		int sended = 0;//已发送字节数
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
		if (actualLen != NULL)
		{
			*actualLen = sended;
		}
		return b;
	}

	void CTcpClient::SendTcpEvt(TcpEvtType type, TCHAR* msg)
	{
		if (m_lpfnOnRecvTcpEvt)
		{
			if (!m_lpfnOnRecvTcpEvt(type, msg))
			{
				if (msg)
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
			SendTcpEvt(TcpEvtType::disconnected, msg);
			if (m_nAllowReconnectCount > 0)//有限次数重连
			{
				m_nReconnectCount++;
				if (m_nReconnectCount == m_nAllowReconnectCount)//已达到重连次数
				{
					m_nReconnectCount = 0;//充值重连次数
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

	DWORD WINAPI ConnectServer(LPVOID lpParam)
	{
		CTcpClient* p = (CTcpClient*)lpParam;
		p->ConnectServer();
		return 0;
	}

	void CTcpClient::ConnectServer()
	{
		while (true)
		{
			int result = ::connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
			if (result == SOCKET_ERROR)
			{
				if (m_nAllowReconnectCount == 0 || (m_nAllowReconnectCount > 0 && m_nReconnectCount < m_nAllowReconnectCount))//判断是否需要重连
				{
					m_nReconnectCount++;
					SendTcpEvt(TcpEvtType::disconnected, _T("failed to connect server \n"));
					Sleep(m_nReconnectTimeSpan);//连接失败后休眠指定时间继续连接
				}
				else
				{
					PauseThread(&m_tiConnect, true);
				}
			}
			else
			{
				OnConnectSuccess();//连接成功
				PauseThread(&m_tiConnect, true);
			}
		}
	}

	void CTcpClient::PauseThread(ThreadInfo* ti, bool b)
	{
		if (ti->hThread != 0)
		{
			if (b)
			{
				if (!ti->bPause)
				{
					ti->bPause = true;
					::SuspendThread(ti->hThread);
				}
			}
			else
			{
				if (ti->bPause)
				{
					ti->bPause = false;
					::ResumeThread(ti->hThread);
				}
			}
		}
	}

	void CTcpClient::InitServerAddr()
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