#pragma once
#include <vector>
#include "SocketAPI.h"
#include "TcpSrvEvt.h"

using namespace std;
using namespace NetworkCommunication;

#ifndef MAXCLIENTCOUNT
#define MAXCLIENTCOUNT	65535	//���ͻ���������
#endif 

#ifndef TCPRECVBUFFERSIZE
#define TCPRECVBUFFERSIZE	2048	//tcp���ջ�������С
#endif 

#ifndef MAXIPSTRELN
#define MAXIPSTRELN	20	//ip�ַ�����󳤶�
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

//����˹����Ŀͻ���socket���ݽṹ
typedef struct tagServerClientSocket
{
	SOCKET scClient;//����ͻ���socket
	SOCKET server;//�����ķ����socket
	TCHAR ip[MAXIPSTRELN];//�ͻ���IP
	int	port;//�ͻ��˶˿�
}ClientSocketData;

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
		SocketExcept,//socket�������쳣
		NetError//�������������
	};
};

//tcp�����¼�
class ETcpSrvEvent
{
public:
	enum
	{
		None,//��
		RecvNewConnection,//�յ�������
		RefuseNewConnection,//�ܾ�������
		RecvPeerData,//�յ��Զ�����
		TcpDisconnect,//tcp���ӶϿ�
		AsyncSendDataResult//�첽�������ݽ��
	};
};

//tcp���ӶϿ�ԭ��
class ETcpDisconnectReason
{
public:
	enum
	{
		Peer,//�Զ������Ͽ�
		Local,//���������Ͽ�
		Except//socket�쳣
	};
};

//select����socket����
class ESelectSocketType
{
public:
	enum
	{
		None,//��
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
//pEvent	tcp�����¼�
typedef void(*LPTcpEventCallback)(CTcpSrvEvt* pEvent);