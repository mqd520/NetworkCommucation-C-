#pragma once


#include "stdafx.h"
#include "MyTcp.h"

#ifdef _DEBUG
#define new new(__FILE__, __LINE__)
#endif

#define ClientCount 2

//�߳̾��
HANDLE hThread = 0;
//�߳�ID
DWORD threadID = 0;
SOCKET socketListen;
SOCKADDR_IN addrClientList[ClientCount];
SOCKET socClientList[ClientCount];

DWORD WINAPI WaitConnect(LPVOID lpParam);

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
				hThread = ::CreateThread(NULL, 0, WaitConnect, NULL, NULL, &threadID);
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
		closesocket(socClientList[i]);
	}
	_tprintf(_T("�ѹرտͻ�������Socket\n"));
	closesocket(socketListen);
	_tprintf(_T("�ѹرշ����Socket\n"));
	WSACleanup();
}


DWORD WINAPI WaitConnect(LPVOID lpParam)
{
	int i = 0;
	int len = sizeof(SOCKADDR);
	while (true)
	{
		//�ͻ�����������,�������¿ͻ�������
		if (i == ClientCount - 1)
		{
			continue;
		}

		//�ȴ��ͻ�������
		SOCKET socClient = accept(socketListen, (SOCKADDR *)&addrClientList[i], &len);
		_tprintf(_T("�յ��¿ͻ�������: %s:%d\n"), inet_ntoa(addrClientList[i].sin_addr), (int)addrClientList[i].sin_port);
		socClientList[i] = socClient;
		if (i == ClientCount - 1)
		{
			_tprintf(_T("���������%d���ͻ�������!,���ٽ����¿ͻ�������!\n"), ClientCount);
			break;
		}
		i++;
	}
	CleanSocket();
	return 0;
}

