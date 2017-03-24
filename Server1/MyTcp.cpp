#pragma once

#include "stdafx.h"
#include "MyTcp.h"

#ifdef _DEBUG
#define new new(__FILE__, __LINE__)
#endif

#define ClientCount 2

//Socket��Ϣ
struct SocketInfo
{
	SOCKET socket;
	bool connected;
	SOCKADDR_IN addr;
};

//�߳���Ϣ
struct ThreadInfo
{
	HANDLE hThread;
	DWORD nThread;
};

DWORD WINAPI WaitConnect(LPVOID lpParam);
DWORD WINAPI ListenClientSocketStatus(LPVOID lpParam);
DWORD WINAPI Recv(LPVOID lpParam);

SOCKET socketListen;
vector<SocketInfo> socClientList;
vector<ThreadInfo> vecThread;

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
				ThreadInfo info1 = {}, info2 = {};
				info1.hThread = ::CreateThread(NULL, 0, WaitConnect, NULL, NULL, &info1.nThread);
				vecThread.push_back(info1);
				info2.hThread = ::CreateThread(NULL, 0, ListenClientSocketStatus, NULL, NULL, &info2.nThread);
				vecThread.push_back(info2);
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

void CleanSocket()
{
	for (int i = 0; i < ClientCount; i++)
	{
		closesocket(socClientList[i].socket);
	}
	_tprintf(_T("�ѹرտͻ�������Socket\n"));
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
		int socketLen = socClientList.size();
		//�ͻ�����������,�������¿ͻ�������
		if (socketLen == ClientCount)
		{
			continue;
		}

		SocketInfo info = {};

		//�ȴ��ͻ�������
		SOCKET socClient = accept(socketListen, (SOCKADDR *)&info.addr, &len);
		_tprintf(_T("�յ��¿ͻ�������: %s:%d\n"), inet_ntoa(info.addr.sin_addr), (int)info.addr.sin_port);

		info.connected = true;
		info.socket = socClient;
		socClientList.push_back(info);

		ThreadInfo info1 = {};
		info1.hThread = ::CreateThread(NULL, 0, Recv, (LPVOID)socClient, NULL, &info1.nThread);
		vecThread.push_back(info1);

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
		Sleep(2 * 1000);
		for (int i = 0; i < (int)socClientList.size();)
		{
			if (!SendData(socClientList[i].socket, _T("OK")))
			{
				closesocket(socClientList[i].socket);
				socClientList.erase(socClientList.begin() + i);
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
	int len = sizeof(data);
	int val = send(socket, data, len, 0);
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