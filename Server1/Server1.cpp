// Server1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define ListenPort	8011
#define ListenIP	_T("127.0.0.1")
#define MaxListenNum	1000


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsData;
	if (WSAStartup(MAKEWORD(2, 2), &wsData) == 0)
	{
		//����socket
		SOCKET soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		//����������ַ
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(ListenPort);
		addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//�󶨱�������IP��ַ
		//addr.sin_addr.S_un.S_addr = htonl(inet_addr(ListenIP));//��ָ��IP��ַ

		//��socket�ͼ�����ַ
		int rec = bind(soc, (SOCKADDR *)&addr, sizeof(SOCKADDR_IN));
		if (rec != SOCKET_ERROR)
		{
			_tprintf(_T("��Socket�ɹ�\n"));

			//��ʼ����
			int rec1 = listen(soc, MaxListenNum);
			if (rec != SOCKET_ERROR)
			{
				_tprintf(_T("�����ɹ�: %s:%d\n"), ListenIP, ListenPort);

				SOCKADDR_IN addrClient;
				int len = sizeof(SOCKADDR);
				while (true)
				{
					//�ȴ��ͻ�������
					SOCKET socClient = accept(soc, (SOCKADDR *)&addrClient, &len);
					_tprintf(_T("�յ��ͻ�������: %s:%d\n"), inet_ntoa(addrClient.sin_addr), (int)addrClient.sin_port);
					
					Sleep(2 * 1000);
					_tprintf(_T("�Ͽ��ͻ���Socket\n"));
					closesocket(socClient);
				}
				closesocket(soc);
				WSACleanup();
			}
			else
			{
				closesocket(soc);
				WSACleanup();
				_tprintf(_T("����ʧ��(%d): %s:%d\n"), WSAGetLastError(), ListenIP, ListenPort);
			}
		}
		else
		{
			closesocket(soc);
			WSACleanup();
			_tprintf(_T("��Socketʧ��(%d): %d\n"), WSAGetLastError(), rec);
		}
	}
	else
	{
		_tprintf(_T("Socketģ������ʧ��!\n"));
	}
	return 0;
}

