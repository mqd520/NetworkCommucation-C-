// Server1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define ListenPort	80
#define ListenIP	_T("127.0.0.1")
#define ClientCount	3


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
		//addr.sin_addr.S_un.S_addr = inet_addr(ListenIP);//��ָ��IP��ַ

		//��socket�ͼ�����ַ
		int rec = bind(soc, (SOCKADDR *)&addr, sizeof(SOCKADDR_IN));
		if (rec != SOCKET_ERROR)
		{
			_tprintf(_T("��Socket�ɹ�\n"));

			//��ʼ����
			int rec1 = listen(soc, 0);
			if (rec != SOCKET_ERROR)
			{
				_tprintf(_T("�����ɹ�: %s:%d\n"), ListenIP, ListenPort);
				_tprintf(_T("�ͻ���������%d��,����˽��Զ��ر�Socket\n"), ClientCount);

				SOCKADDR_IN addrClientList[ClientCount];
				SOCKET socClientList[ClientCount];
				int i = 0;
				int len = sizeof(SOCKADDR);
				while (true)
				{
					//�ȴ��ͻ�������
					SOCKET socClient = accept(soc, (SOCKADDR *)&addrClientList[i], &len);
					_tprintf(_T("�յ��¿ͻ�������: %s:%d\n"), inet_ntoa(addrClientList[i].sin_addr), (int)addrClientList[i].sin_port);
					socClientList[i] = socClient;

					if (i == ClientCount - 1)
					{
						_tprintf(_T("���������%d���ͻ�������!\n"), ClientCount);
						break;
					}
					i++;
				}
				for (int i = 0; i < ClientCount; i++)
				{
					closesocket(socClientList[i]);
				}
				_tprintf(_T("�ѹرտͻ�������Socket\n"));
				closesocket(soc);
				_tprintf(_T("�ѹرշ����Socket\n"));
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

	system("pause");
	return 0;
}

