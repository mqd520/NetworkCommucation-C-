#pragma once
#include <vector>
#include "SocketAPI.h"
#include "TcpAction.h"

using namespace std;
using namespace NetworkCommunication;

#ifndef MAXCLIENTCOUNT
#define MAXCLIENTCOUNT	65535	//���ͻ���������
#endif 

#ifndef TCPRECVBUFFERSIZE
#define TCPRECVBUFFERSIZE	2048	//tcp���ջ�������С
#endif 

//socket���ͽ�������
class ESocketSendRecvType
{
public:
	enum
	{
		Recv,	//��������
		Send	//��������
	};
};

//�Զ˽�������
typedef struct tagPeerData
{
	SOCKET socket;//�������ݵ�socket
	BYTE* pBuf;//���յ�������
	int len;//���յ������ݳ���
	TCHAR ip[20];//�Զ�IP
	int port;//�Զ˶˿�
}PeerData;

//����˹����Ŀͻ���socket���ݽṹ
typedef struct tagServerClientSocket
{
	SOCKET scClient;//����ͻ���socket
	SOCKET server;//�����ķ����socket
	TCHAR ip[20];//�ͻ���IP
	int	port;//�ͻ��˶˿�
}ClientSocketData;

//�ͻ���socket���ݽṹ
//typedef struct tagClientSocket
//{
//	SOCKET client;//�ͻ���socket
//	TCHAR clientIP[20];//�ͻ���IP
//	int clientPort;//�ͻ��˶˿�
//	TCHAR serverIP[20];//�����IP
//	int serverPort;//����˶˿�
//}ClientSocket;

//tcp��������
class ETcpServiceType
{
public:
	enum
	{
		Client,	//�ͻ���
		Server	//�����
	};
};

//tcp��������
class ETcpActionType
{
public:
	enum
	{
		RecvNewConnection,//�յ�������
		RecvPeerData,//�յ��Զ�����
		PeerCloseConn,//�Զ������ر�����
		AsyncSendData,//�첽��������
		SendDataResult,//�������ݽ��
		NetError,//�������������
		RefuseNewConn//�ܾ��ͻ�������
	};
};

//select����socket����
class ESelectSocketType
{
public:
	enum
	{
		RecvConn,//ָʾ���ڽ��������ӵ�socket
		ReadWriteData//ָʾ���ڶ�д���ݵ�socket
	};
};

//select����socket���ݽṹ
typedef struct tagSelectSocketData
{
	SOCKET	socket;//socket
	int		type;  //select����socket����
}SelectSocketData;

//��Զ˷������ݽ��
typedef struct tagSendPeerDataResult
{
	TCHAR ip[20];//�Զ�IP
	int port;//�Զ˶˿�
	bool success;//�Ƿ�ɹ�
	int len;//���������ֽڳ���
	int actualLen;//ʵ�ʷ����ֽڳ���
}SendPeerDataResult;

//�첽���ͶԶ�����
typedef struct tagAsyncSendPeerData
{
	int len;//���������ֽڳ���
	BYTE* pBuf;//������ָ��
	SOCKET send;//�������ݵ�socket
}AsyncSendPeerData;

//tcp�¼��ص�����ָ��
typedef void(*LPTcpEventCallback)(CTcpAction* action);