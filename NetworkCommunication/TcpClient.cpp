#include "stdafx.h"
#include "TcpClient.h"
#include "NetTool.h"
#include "StringHandle.h"

namespace NetworkCommunication
{
	//连接服务端线程入口
	DWORD WINAPI ConnectServer(LPVOID lpParam);

	//读取tcp数据线程入口
	DWORD WINAPI ReadTcpData(LPVOID lpParam);

	//多线程发送数据线程入口
	DWORD WINAPI MultiSendRecvData(LPVOID lpParam);

	//读取队列数据线程入口
	DWORD WINAPI ReadQueue(LPVOID lpParam);

	//多线程发送tcp数据线程参数
	typedef struct tagMultiSendTcpDataThreadPara
	{
		CTcpClient* pClient;//客户端指针
		BufInfo buf;//缓冲区信息
	}MultiSendTcpDataThreadPara, *LPMultiSendTcpDataThreadPara;

	CTcpClient::CTcpClient() :
		m_nRecvTcpBufLen(0),
		m_pRecvTcpBuf(NULL),
		m_strServerIP(NULL),
		m_nServerPort(0),
		m_socket(0),
		m_addrSrv({ 0 }),
		m_lpfnOnRecvTcpEvt(NULL),
		m_bHaslpfnRecvTcpData(false),
		m_nReconnectTimeSpan(3000),
		m_nAllowReconnectCount(0),
		m_nReconnectCount(0),
		m_nConnectTimeout(2 * 1000),
		m_tiConnect({ 0 }),
		m_bSocketClosed(true),
		m_timer(NULL),
		m_sendType(TcpDataSendType::single),
		m_tiQueue({ 0 })
	{

	}

	CTcpClient::~CTcpClient()
	{
		CloseConnect();
		CleanThread();
		WSACleanup();
		if (m_pRecvTcpBuf)
		{
			delete m_pRecvTcpBuf;
			m_pRecvTcpBuf = NULL;
		}
		if (m_timer)
		{
			delete m_timer;
		}
	}

	void CTcpClient::Init(const TCHAR* ip, int port, TcpDataSendType type, int socketBufLen, int allowReconnectCount, int reconnectTimeSpan,
		int connectTimeout)
	{
		if (!m_bInited)
		{
			m_sendType = type;
			m_nAllowReconnectCount = allowReconnectCount;
			m_nReconnectTimeSpan = reconnectTimeSpan;
			m_bInited = true;
			m_nRecvTcpBufLen = socketBufLen;
			m_pRecvTcpBuf = new char[socketBufLen];
			m_strServerIP = ip;
			m_nServerPort = port;
			if (connectTimeout > 0)//连接有超时时间
			{
				m_timer = new CTimerT<CTcpClient>(connectTimeout);
				m_timer->SetCallbackT(&CTcpClient::OnConnectTimeout, this);
			}
			if (m_sendType == TcpDataSendType::que)//创建队列线程
			{
				m_tiQueue.hThread = ::CreateThread(NULL, 0, NetworkCommunication::ReadQueue, this, NULL, &m_tiQueue.dwThreadID);
			}
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
		else
		{
			m_bSocketClosed = false;
		}
	}

	void CTcpClient::OnConnectSuccess()
	{
		m_nReconnectCount = 0;
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

	bool CTcpClient::OnConnectTimeout()
	{
		CloseSocket();
		return false;
	}

	void CTcpClient::Connect()
	{
		CloseConnect();//关闭可能已经存在的连接
		CreateSocket();//重新创建客户端socket
		if (m_tiConnect.hThread == 0)
		{
			//启动连接线程
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
		CloseSocket();
		PauseThread(&m_tiConnect, true);
		PauseThread(&m_tiReadTcpData, true);
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
			memset(m_pRecvTcpBuf, 0, m_nRecvTcpBufLen);//接收缓冲区清零
			int len = recv(m_socket, m_pRecvTcpBuf, m_nRecvTcpBufLen, 0);
			if (len > 0 && m_bHaslpfnRecvTcpData)
			{
				BYTE* buf = new BYTE[len];
				memcpy(buf, m_pRecvTcpBuf, len);
				OnRecvTcpData(buf, len);
			}
			else
			{
				if (len == 0)//连接被关闭
				{
					SendTcpEvt(disconnected, _T("server disconnect the connection! \n"));
				}
				else if (len == -1)//网络故障
				{
					SendTcpEvt(disconnected, _T("Net trouble happended! \n"));
				}
				if (m_nAllowReconnectCount != -1)//允许重连
				{
					Connect();//重连连接
				}
				PauseThread(&m_tiReadTcpData, true);//挂起读取tcp数据线程
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

	void CTcpClient::SimulateServerData(BYTE* buf, int len)
	{
		BYTE* buf1 = new BYTE[len];
		memcpy(buf1, buf, len);
		OnRecvTcpData(buf1, len);
	}

	void CTcpClient::OnRecvTcpData(BYTE buf[], int len)
	{
		switch (m_sendType)
		{
		case NetworkCommunication::que:
			OnQueue(buf, len);
			break;
		case NetworkCommunication::single:
			OnSingle(buf, len);
			break;
		case NetworkCommunication::multi:
			OnMulti(buf, len);
			break;
		default:
			delete buf;
			break;
		}
	}

	void CTcpClient::OnSingle(BYTE buf[], int len)
	{
		SendTcpData(buf, len);
	}

	void CTcpClient::OnQueue(BYTE buf[], int len)
	{
		m_queue.push({ buf, len });
		PauseThread(&m_tiQueue, false);
	}

	void CTcpClient::OnMulti(BYTE buf[], int len)
	{
		LPMultiSendTcpDataThreadPara p = new MultiSendTcpDataThreadPara{ this, { buf, len } };
		::CreateThread(NULL, 0, NetworkCommunication::MultiSendRecvData, p, NULL, NULL);
	}

	void CTcpClient::SendTcpData(BYTE buf[], int len)
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
			if (m_timer)//指定了连接超时时间
			{
				if (m_bSocketClosed)//socket可能因为上一次连接超时而被关闭
				{
					CreateSocket();//重新创建socket
				}
				m_timer->Start();//开始计时
			}
			int result = ::connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
			if (m_timer)//指定了连接超时时间
			{
				if (!m_timer->IsTimeoutCmp())//连接没有超时,停止本次计时
				{
					m_timer->Stop();
				}
			}
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

	void CTcpClient::CleanThread()
	{
		if (m_tiConnect.hThread)
		{
			::TerminateThread(m_tiConnect.hThread, 0);
			::CloseHandle(m_tiConnect.hThread);
		}
		if (m_tiReadTcpData.hThread)
		{
			::TerminateThread(m_tiReadTcpData.hThread, 0);
			::CloseHandle(m_tiReadTcpData.hThread);
		}
		if (m_tiQueue.hThread)
		{
			::TerminateThread(m_tiQueue.hThread, 0);
			::CloseHandle(m_tiQueue.hThread);
		}
	}

	void CTcpClient::CloseSocket()
	{
		::closesocket(m_socket);
		m_bSocketClosed = true;
	}

	DWORD WINAPI MultiSendRecvData(LPVOID lpParam)
	{
		LPMultiSendTcpDataThreadPara p = (LPMultiSendTcpDataThreadPara)lpParam;
		p->pClient->MultiSendTcpData(p->buf.buf, p->buf.len);
		delete p;
		return 0;
	}

	void CTcpClient::MultiSendTcpData(BYTE buf[], int len)
	{
		SendTcpData(buf, len);
	}

	DWORD WINAPI ReadQueue(LPVOID lpParam)
	{
		CTcpClient* p = (CTcpClient*)lpParam;
		p->ReadQueue();
		return 0;
	}

	void CTcpClient::ReadQueue()
	{
		while (true)
		{
			if (m_queue.empty())//队列空了，应该挂起线程
			{
				PauseThread(&m_tiQueue, true);
			}
			else
			{
				BufInfo bufinfo = m_queue.front();
				BYTE* buf = bufinfo.buf;
				int len = bufinfo.len;
				m_queue.pop();
				SendTcpData(buf, len);
			}
		}
	}
}