#include "stdafx.h"
#include "TcpClient.h"
#include "NetTool.h"
#include "Common.h"

using namespace Common;

//��ʼ��ȡ����
DWORD WINAPI StartReadData(LPVOID lpParam);

CTcpClient::CTcpClient()
{
	m_strIP = NULL;
	m_nPort = NULL;
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

//��ʼ��
void CTcpClient::Init(const TCHAR* ip, int port, LPOnRecvData lpfn)
{
	m_bInited = true;
	m_strIP = ip;
	m_nPort = port;
	m_lpOnRecvData = lpfn;
}

//��ʼ��Socket
bool CTcpClient::InitSocket()
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
	string strTmp = UTF8ToMultiByte(m_strIP);
	m_addrSrv.sin_addr.S_un.S_addr = inet_addr(strTmp.c_str());
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
	if (InitSocket())
	{
		int result = connect(m_socket, (SOCKADDR*)&m_addrSrv, sizeof(m_addrSrv));
		if (result == SOCKET_ERROR)
		{
			_tprintf(_T("���ӷ����ʧ��: %s:%d\n"), m_strIP, m_nPort);
			CleanSocket();
			return false;
		}
		m_readThreadInfo.hThread = ::CreateThread(NULL, 0, StartReadData, this, NULL, &m_readThreadInfo.nThreadID);
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
			pTCPClient->OnRecvData((BYTE*)buf, len);
		}
	}
	return 0;
}

//���������¼�
void CTcpClient::OnRecvData(BYTE buf[], int len)
{
	if (m_lpOnRecvData)
	{
		BYTE* buf1 = new BYTE[len];
		memcpy(buf1, buf, len);
		try
		{
			m_lpOnRecvData(buf, len);
			if (buf1)
			{
				delete buf1;
			}
		}
		catch (int)
		{
			delete buf1;
		}
	}
}

//�����߳�
void CTcpClient::CleanThread()
{
	if (m_readThreadInfo.hThread > 0)
	{
		::TerminateThread(m_readThreadInfo.hThread, 0);
		::CloseHandle(m_readThreadInfo.hThread);
		m_readThreadInfo = { 0 };
	}
}

//�����ͷ���Դ
void CTcpClient::Dispose()
{
	CleanSocket();
	CleanThread();
}

//��������
bool CTcpClient::SendData(BYTE buf[], int len)
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
bool CTcpClient::IsInited()
{
	return m_bInited;
}