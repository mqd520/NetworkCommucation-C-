#include "stdafx.h"
#include "SocketClient.h"
#include "NetTool.h"
#include "Common.h"

namespace TCPCommunication
{
	//��ʼ��ȡ����
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

	//��ʼ��
	void CSocketClient::Init(const TCHAR* ip, int port, LPOnRecvTCPData lpfn)
	{
		m_bInited = true;
		m_strServerIP = ip;
		m_nServerPort = port;
		m_strClientIP = NULL;
		m_nClientPort = 0;
		m_lpOnRecvData = lpfn;
	}

	//��ʼ��Socket
	bool CSocketClient::InitSocket()
	{
		WSADATA wsaData;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			_tprintf(_T("Socket��ʼ��ʧ��!\n"));
			return false;
		}

		//��������˵�ַ
		m_addrSrv.sin_family = AF_INET;
		m_addrSrv.sin_port = htons(m_nServerPort);
#ifdef _UNICODE
		string strTmp = UTF8ToMultiByte(m_strServerIP);
		m_addrSrv.sin_addr.S_un.S_addr = inet_addr(strTmp.c_str());
#else
		m_addrSrv.sin_addr.S_un.S_addr = inet_addr(m_strServerIP);
#endif

		//�����ͻ���Socket
		m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		SetAddressBySocket(m_socket);
		if (m_socket == INVALID_SOCKET)
		{
			_tprintf(_T("����Socketʧ��: %d\n"), WSAGetLastError());
			CleanSocket();
			return false;
		}

		return true;
	}

	//������Դ
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

	//���ӵ������
	bool CSocketClient::StartConnect()
	{
		if (InitSocket())
		{
			int result = connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
			if (result == SOCKET_ERROR)
			{
				_tprintf(_T("���ӷ����ʧ��: %s:%d\n"), m_strServerIP, m_nServerPort);
				CleanSocket();
				return false;
			}
			m_readThreadInfo.hThread = ::CreateThread(NULL, 0, StartReadData, this, NULL, &m_readThreadInfo.nThreadID);
			return true;
		}
		return false;
	}

	//��ȡ���һ�δ�����Ϣ
	TCHAR* CSocketClient::GetLastError()
	{
		return m_strLastError;
	}

	//�ر�����������
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

	//��ȡSocket
	SOCKET CSocketClient::GetServerSocket()
	{
		return m_socket;
	}

	//��ʼ��ȡ����
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

	//���������¼�
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

	//�����߳�
	void CSocketClient::CleanThread()
	{
		if (m_readThreadInfo.hThread > 0)
		{
			::TerminateThread(m_readThreadInfo.hThread, 0);
			::CloseHandle(m_readThreadInfo.hThread);
			m_readThreadInfo = { 0 };
		}
	}

	//�����ͷ���Դ
	void CSocketClient::Dispose()
	{
		CleanSocket();
		CleanThread();
	}

	//��������
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

	//�Ƿ��ѳ�ʼ��
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