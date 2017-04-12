#include "stdafx.h"
#include "MyTcp.h"

#ifdef _DEBUG
#define new new(__FILE__, __LINE__)
#endif

#define ClientCount 2

//Socket��Ϣ
typedef struct tagSocketInfo
{
	SOCKET socket;
	bool connected;
	SOCKADDR_IN addr;
}SocketInfo;

//�߳���Ϣ
typedef struct tagThreadInfo
{
	HANDLE hThread;
	DWORD nThread;
}ThreadInfo;

//�̹߳���
typedef struct tagThreadMgr
{
	ThreadInfo wait;
	ThreadInfo status;
	vector<ThreadInfo> recv;
}ThreadMgr;

DWORD WINAPI WaitConnect(LPVOID lpParam);
DWORD WINAPI ListenClientSocketStatus(LPVOID lpParam);
DWORD WINAPI Recv(LPVOID lpParam);
void CleanSocket();

//����˶���
SOCKET socketListen;
//�ͻ���Socket����
vector<SocketInfo> vecSocketList;
//�̹߳������
ThreadMgr trdMgr = {};

void StartListen(TCHAR* ip, int port)
{
	WSADATA wsData;
	if (WSAStartup(MAKEWORD(2, 2), &wsData) == 0)
	{
		//����socket
		socketListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		//����������ַ
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		TCHAR* showIP;//��ʾIP
		if (ip == NULL)
		{
			addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//�󶨱�������IP��ַ
			showIP = _T("127.0.0.1");
		}
		else
		{
			addr.sin_addr.S_un.S_addr = inet_addr(ip);//��ָ��IP��ַ
			showIP = ip;
		}

		//��socket�ͼ�����ַ
		int rec = bind(socketListen, (SOCKADDR *)&addr, sizeof(SOCKADDR_IN));
		if (rec != SOCKET_ERROR)
		{
			_tprintf(_T("��Socket�ɹ�\n"));

			//��ʼ����
			int rec1 = listen(socketListen, 0);
			if (rec != SOCKET_ERROR)
			{
				_tprintf(_T("�����ɹ�\n"), showIP, port);
				trdMgr.wait.hThread = ::CreateThread(NULL, 0, WaitConnect, NULL, NULL, &trdMgr.wait.nThread);
				trdMgr.status.hThread = ::CreateThread(NULL, 0, ListenClientSocketStatus, NULL, NULL, &trdMgr.status.nThread);
			}
			else
			{
				closesocket(socketListen);
				WSACleanup();
				_tprintf(_T("����ʧ��(%d): %s:%d\n"), WSAGetLastError(), showIP, port);
			}
		}
		else
		{
			closesocket(socketListen);
			WSACleanup();
			_tprintf(_T("��Socketʧ��(%d): %d\n"), WSAGetLastError(), rec);
		}
	}
	else
	{
		_tprintf(_T("Socketģ������ʧ��!\n"));
	}
}

//����Socket
void CleanSocket()
{
	if (vecSocketList.size() > 0)
	{
		for (int i = 0; i < (int)vecSocketList.size(); i++)
		{
			closesocket(vecSocketList[i].socket);
		}
		_tprintf(_T("�ѹرտͻ�������Socket\n"));
	}
	closesocket(socketListen);
	_tprintf(_T("�ѹرշ����Socket\n"));
	WSACleanup();
}

//�����ͻ��������߳�
DWORD WINAPI WaitConnect(LPVOID lpParam)
{
	int len = sizeof(SOCKADDR);
	while (true)
	{
		int socketLen = vecSocketList.size();
		//�ͻ�����������,�������¿ͻ�������
		if (socketLen == ClientCount)
		{
			continue;
		}

		SocketInfo info = {};

		//�ȴ��ͻ�������
		SOCKET socClient = accept(socketListen, (SOCKADDR *)&info.addr, &len);
		SendData(socClient, NULL);
		_tprintf(_T("�յ��¿ͻ�������: %s:%d\n"), inet_ntoa(info.addr.sin_addr), (int)info.addr.sin_port);

		info.connected = true;
		info.socket = socClient;
		vecSocketList.push_back(info);

		ThreadInfo info1 = {};
		info1.hThread = ::CreateThread(NULL, 0, Recv, (LPVOID)socClient, NULL, &info1.nThread);
		trdMgr.recv.push_back(info1);

		if (socketLen == ClientCount - 1)
		{
			_tprintf(_T("���������%d���ͻ�������!,���ٽ����¿ͻ�������!\n"), ClientCount);
		}
	}
	return 0;
}

//�����ͻ���Socket״̬
DWORD WINAPI ListenClientSocketStatus(LPVOID lpParam)
{
	while (true)
	{
		Sleep(1 * 1000);
		for (int i = 0; i < (int)vecSocketList.size();)
		{
			if (!SendData(vecSocketList[i].socket, _T("OK")))
			{
				closesocket(vecSocketList[i].socket);
				vecSocketList.erase(vecSocketList.begin() + i);
				_tprintf(_T("ʧȥһ���ͻ�������\n"));
			}
			else
			{
				i++;
			}
		}
	}
}

bool SendData(SOCKET socket, TCHAR* data)
{
	//int len = _tcslen(data);
	//int val = send(socket, data, len, 0);
	char buf[1] = { 48 };
	int val = send(socket, buf, 1, 0);
	if (val == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}

//��������
DWORD WINAPI Recv(LPVOID lpParam)
{
	SOCKET socket = (SOCKET)lpParam;
	while (true)
	{
		TCHAR buf[1024] = { '\0' };
		int len = recv(socket, buf, 1024, 0);
		if (len > 0)
		{
			_tprintf(_T("�յ����ݣ�%s\n"), buf);
		}
	}
}

void Clean()
{
	CleanSocket();
	if (trdMgr.wait.hThread != 0)
	{
		TerminateThread(trdMgr.wait.hThread, 0);
	}
	if (trdMgr.status.hThread != 0)
	{
		TerminateThread(trdMgr.status.hThread, 0);
	}
	for (int i = 0; i < (int)trdMgr.recv.size(); i++)
	{
		TerminateThread(trdMgr.recv[i].hThread, 0);
	}
}