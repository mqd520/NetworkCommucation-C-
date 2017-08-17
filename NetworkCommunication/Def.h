#pragma once
#include <vector>
#include "SocketAPI.h"

using namespace std;

#ifndef MAXCLIENTCOUNT
#define MAXCLIENTCOUNT	65535	//���ͻ���������
#endif 

#ifndef TCPBUFFERSIZE
#define TCPBUFFERSIZE	2048	//tcp��������С
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

//socket��������
typedef struct tagSocketRecvData
{
	SOCKET peer;//�Զ�socket
	BYTE* pBuf;//���յ�������
	int len;//���յ������ݳ���
	int type;//socket���ͽ�������
}SocketRecvData;

//�����socket��������
typedef struct tagServerSocketRelationData
{
	SOCKET socket;//�����socket
	char ip[20];//������IP
	int port;//�����Ķ˿�
	SOCKADDR_IN addr;//����˵�ַ
	vector<TCHAR*> vecAllowIP;//����ָ��IP���ӷ����
	void* tcpServer;
}ServerSocketData;

//tcp��������socket����
typedef struct tagSocketPair
{
	SOCKET local;//����socket
	SOCKET peer;//�Զ�socket
}SocketPair;

typedef struct tagPeerSocketData
{
	SOCKET peer;//�Զ�socket
	char ip[20];//�Զ�IP
	int	port;//�Զ˶˿�
	SOCKET local;//�����ı���socket
}PeerSocketData;

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
		AcceptNewConnection,//���յ��µĿͻ�������
		PeerClose,//�Զ������ر�
		RecvPeerData,//�յ��Զ�socket����
		SendPeerDataResult,//�������ݽ��
		SendData//��Զ˷�������
	};
};

//select����socket����
class ESelectSocketType
{
public:
	enum
	{
		Server,//�����socket
		Peer//�Զ�socket
	};
};

//select����socket���ݽṹ
typedef struct tagSelectSocketData
{
	SOCKET	socket;//socket
	int		type;  //select����socket����
}SelectSocketData;

//���ͶԶ�socket���ݽ��
typedef struct tagSendPeerDataResult
{
	char ip[20];//�Զ�IP
	int port;//�Զ˶˿�
	bool success;//�Ƿ�ɹ�
	int len;//���������ֽڳ���
	SOCKET peer;//�Զ�socket
}SendPeerDataResult;