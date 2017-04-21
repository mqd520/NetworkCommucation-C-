#include "stdafx.h"
#include "TcpClient.h"
#include "NetTool.h"
#include "StringHandle.h"

namespace NetworkCommunication
{
	//����tcp�����߳����
	DWORD WINAPI OnRecvTcpData(LPVOID lpParam);

	//��ȡtcp�����߳����
	DWORD WINAPI ReadTcpData(LPVOID lpParam);

	//���ӷ�����߳����
	//DWORD WINAPI ConnectServer(LPVOID lpParam);

	//���ӷ�����߳����
	DWORD WINAPI ConnectServer(LPVOID lpParam);

	//��ʱ�߳����
	DWORD WINAPI Timeout(LPVOID lpParam);

	//���������߳���ڲ���
	typedef struct tagRecvDataThreadEntryPara
	{
		CTcpClient* pClient;//�ͻ���ָ��
		BYTE* buf;//������
		int nlen;//����������
	}RecvDataThreadEntryPara, *LPRecvDataThreadEntryPara;

	//��ʱ�߳���ڲ���
	typedef struct tagTimeoutThreadEntryPara
	{
		CTcpClient* pClient;//�ͻ���ָ��
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
			SendTcpEvt(TcpEvtType::error, _T("Socket��ʼ��ʧ��!\n"));
		}
	}

	void CTcpClient::CreateSocket()
	{
		m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_socket == INVALID_SOCKET)
		{
			SendTcpEvt(TcpEvtType::error, _T("����Socketʧ��!\n"));
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
	//		if (m_nConnectTimeout > 0)//���ӳ�ʱʱ�䲻Ϊ0ʱ��������ʱ�߳�
	//		{
	//			m_bConnectedTimeout = true;//ָʾ�����ѳ�ʱ
	//			m_tiConnectTimeout.hThread = ::CreateThread(NULL, 0, Timeout, this, NULL, &(m_tiConnectTimeout.dwThreadID));
	//		}
	//		int result = connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
	//		if (m_nConnectTimeout > 0)
	//		{
	//			m_bConnectedTimeout = false;//ָʾ��������,û�г�ʱ
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
		if (m_tiReadTcpData.hThread == 0)//������ȡtcp�����߳�
		{
			m_tiReadTcpData.hThread = ::CreateThread(NULL, 0, NetworkCommunication::ReadTcpData, this, NULL, &m_tiReadTcpData.dwThreadID);
		}
		else
		{
			PauseThread(&m_tiReadTcpData, false);//�ָ���ȡtcp�����߳�
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
		CloseConnect();//�رտ����Ѿ����ڵ�����
		CreateSocket();//���´����ͻ���socket
		if (m_tiConnect.hThread == 0)
		{
			//�������ӷ�����߳�
			m_tiConnect.hThread = ::CreateThread(NULL, 0, NetworkCommunication::ConnectServer, this, NULL, &m_tiConnect.dwThreadID);
		}
		else
		{
			//�ָ��ѹ���������߳�
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
				if (len == 0)//����������Ͽ�����
				{
					OnLoseConnect(LoseConnectReason::Server);
				}
				else if (len == -1)//�������
				{
					OnLoseConnect(LoseConnectReason::Net);
				}
			}
		}
	}

	bool CTcpClient::SendData(BYTE buf[], int len, int* actualLen)
	{
		bool b = false;
		int sended = 0;//�ѷ����ֽ���
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

		m_tiConnectTimeout = { 0 };//�������ӳ�ʱ�߳���Ϣ

		if (m_bExitThread)//ָʾӦ���˳��߳�
		{
			return;
		}

		if (m_bConnectedTimeout)//ָʾ�����ѳ�ʱ,���Խ��г�ʱ����
		{
			if (m_tiConnect.hThread)
			{
				::TerminateThread(m_tiConnect.hThread, 0);
				m_tiConnect = { 0 };
			}

			bool connect = false;//�Ƿ�Ӧ��������������
			TCHAR msg[100];
			wsprintf(msg, _T("failed to connect server(time out): %s:%d\n"), m_strServerIP, m_nServerPort);
			SendTcpEvt(TcpEvtType::disconnected, msg);
			if (m_nAllowReconnectCount > 0)//���޴�������
			{
				m_nReconnectCount++;
				if (m_nReconnectCount == m_nAllowReconnectCount)//�Ѵﵽ��������
				{
					m_nReconnectCount = 0;//��ֵ��������
					m_bReconnecting = false;//ȡ����������
				}
				else
				{
					connect = true;
				}
			}
			else//����������
			{
				connect = true;
			}
			if (connect)
			{
				//��ʼ����
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
				if (m_nAllowReconnectCount == 0 || (m_nAllowReconnectCount > 0 && m_nReconnectCount < m_nAllowReconnectCount))//�ж��Ƿ���Ҫ����
				{
					m_nReconnectCount++;
					SendTcpEvt(TcpEvtType::disconnected, _T("failed to connect server \n"));
					Sleep(m_nReconnectTimeSpan);//����ʧ�ܺ�����ָ��ʱ���������
				}
				else
				{
					PauseThread(&m_tiConnect, true);
				}
			}
			else
			{
				OnConnectSuccess();//���ӳɹ�
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