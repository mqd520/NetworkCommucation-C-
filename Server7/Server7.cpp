// Server7.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "NetCommuMgr.h"
#include "TcpServer.h"
#include "MemoryTool.h"
#include "RecvPeerDataEvt.h"

void OnRecvTcpEvent(CTcpEvt* pEvent);
BOOL WINAPI HandlerRoutine(DWORD dwCtrlType);

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);

	CNetworkCommuMgr::Init();//����ͨ�ų�ʼ��

	CTcpServer server;
	server.Listen(_T("192.168.0.68"), 8040);
	server.RegTcpEventCallback(OnRecvTcpEvent);

	_tprintf(_T("����exit�˳�����!\n"));
	char input[5];
	while (true)
	{
		scanf("%4s", input, 5);
		if (strcmp(input, "exit") == 0)
		{
			break;
		}
		else
		{
			int len = 0;
			BYTE* buf = WriteMultiByteStr("Leon520����~!@#$%^&*()-=_+[]{};'\\:\"|,./<>?", &len);
			int socket = ::atoi(input);
			bool result = server.SendData((SOCKET)socket, buf, len);//ͬ������
			//server.AsyncSendData((SOCKET)socket, buf, len);//�첽����
		}
	}

	CNetworkCommuMgr::Exit();

	CNetworkCommuMgr::Release();

	return 0;
}

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	if (CTRL_CLOSE_EVENT == dwCtrlType){
		CNetworkCommuMgr::Exit();

		CNetworkCommuMgr::Release();
	}
	return TRUE;
}

void OnRecvTcpEvent(CTcpEvt* pEvent)
{
	switch (pEvent->GetEvtType())
	{
	case ETcpEvent::RecvPeerData:
		CRecvPeerDataEvt* pRecvDataEvt = (CRecvPeerDataEvt*)pEvent;
		printf("Recv data, size: %d \n", pRecvDataEvt->GetBufLen());
		break;
	}
}

