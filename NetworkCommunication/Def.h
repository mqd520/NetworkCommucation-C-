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
	char ip[20];//�Զ�IP
	int port;//�Զ˶˿�
}PeerData;

//�����socket����
typedef struct tagServerSocket
{
	SOCKET socket;//�����socket
	char ip[20];//������IP
	int port;//�����Ķ˿�
	SOCKADDR_IN addr;//����˵�ַ
	vector<TCHAR*> vecAllowIP;//����ָ��IP���ӷ����
	void* tcpServer;//������tcp�������
}ServerSocket;

//����˹����Ŀͻ���socket���ݽṹ
typedef struct tagServerClientSocket
{
	SOCKET scClient;//����ͻ���socket
	char ip[20];//�ͻ���IP
	int	port;//�ͻ��˶˿�
	SOCKET server;//�����ķ����socket
}ServerClientSocket;

//�ͻ���socket���ݽṹ
typedef struct tagClientSocket
{
	SOCKET client;//�ͻ���socket
	char clientIP[20];//�ͻ���IP
	int clientPort;//�ͻ��˶˿�
	char serverIP[20];//�����IP
	int serverPort;//����˶˿�
}ClientSocket;

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
	char ip[20];//�Զ�IP
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