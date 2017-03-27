#include "stdafx.h"
#include "TcpClient.h"
#include "Common.h"

#ifdef _DEBUG
#define new new(__FILE__, __LINE__)
#endif

//��ʼ��ȡ����
DWORD WINAPI StartReadData(LPVOID lpParam);

CTcpClient::CTcpClient(HWND hwnd, const TCHAR* ip, int port)
{
	m_hwnd = hwnd;
	m_strIP = ip;
	m_nPort = port;
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

//Socket��ʼ��
bool CTcpClient::Init()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		_tprintf(_T("Socket��ʼ��ʧ��!\n"));
		return false;
	}

	//��������˵�ַ
	m_addrSrv.sin_family = AF_INET;
	m_addrSrv.sin_port = htons(m_nPort);
#ifdef _UNICODE
	char* strTmp = UTF8ToMultiByte(m_strIP);
	m_addrSrv.sin_addr.S_un.S_addr = inet_addr(strTmp);
	delete strTmp;
#else
	m_addrSrv.sin_addr.S_un.S_addr = inet_addr(m_strIP);
#endif

	//�����ͻ���Socket
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		_tprintf(_T("����Socketʧ��: %d\n"), WSAGetLastError());
		CleanSocket();
		return false;
	}

	return true;
}

//������Դ
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

//���ӵ������
bool CTcpClient::StartConnect()
{
	if (Init())
	{
		int result = connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
		if (result == SOCKET_ERROR)
		{
			_tprintf(_T("���ӷ����ʧ��: %s:%d\n"), m_strIP, m_nPort);
			CleanSocket();
			return false;
		}
		::CreateThread(NULL, 0, StartReadData, this, NULL, &m_readThreadInfo.nThreadID);
		return true;
	}
	return false;
}

//��ȡ���һ�δ�����Ϣ
TCHAR* CTcpClient::GetLastError()
{
	return m_strLastError;
}

//�ر�����������
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

//��ȡSocket
SOCKET CTcpClient::GetServerSocket()
{
	return m_socket;
}

//��ʼ��ȡ����
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
			pTCPClient->OnRecvData(buf, len);
		}
	}
	return 0;
}

//��������
void CTcpClient::OnRecvData(char buf[], int len)
{
	//string s = buf;
	//WriteLine(s);
	char* buf1 = new char[len];
	memcpy(buf1, buf, len);
	::PostMessage(m_hwnd, TCPClientRecvMsg, (WPARAM)buf1, len);
}

//�����߳�
void CTcpClient::CleanThread()
{
	if (m_readThreadInfo.hThread > 0)
	{
		::TerminateThread(m_readThreadInfo.hThread, 0);
	}
}

//�����ͷ���Դ
void CTcpClient::Dispose()
{
	CleanSocket();
	CleanSocket();
}

//��������
bool CTcpClient::SendData(char* buf, int len)
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
		int result = send(m_socket, buf, len - sended, 0);
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