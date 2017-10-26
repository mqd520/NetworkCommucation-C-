#pragma once
#include <vector>
#include "SocketAPI.h"
#include "TcpEvt.h"

using namespace std;
using namespace NetworkCommunication;

#define	NETCOMM_MAXCLIENTCOUNT			65535	//���tcp������
#define NETCOMM_TCPRECVBUFFERSIZE		1024	//tcp���ջ�����Ĭ�ϴ�С
#define NETCOMM_TCPSENDBUFFERSIZE		1024	//tcp�첽���ͻ�����Ĭ�ϴ�С
#define NETCOMM_MAXIPSTRELN				20		//ip�ַ�����󳤶�

//�����ַ
typedef struct tagNetAddress
{
	TCHAR ip[NETCOMM_MAXIPSTRELN];//ip
	int port;//�˿�
}NetAddress;

//tcp�¼�
class ETcpEvent
{
public:
	enum
	{
		RecvNewConnection,//�յ�������
		RefuseNewConnection,//�ܾ�������
		RecvPeerData,//�յ��Զ�����
		ConnDisconnect,//���ӶϿ�
		AsyncSendDataResult,//�첽�������ݽ��
		ConnectCmp//�������
	};
};

//select����socket����
class ESelectSocketType
{
public:
	enum
	{
		RecvConn,//ָʾ���ڽ��������ӵķ����socket
		ReadWriteData,//ָʾ���ڶ�д���ݵ�socket
		Connect//ָʾ�������ӷ���˵Ŀͻ���socket
	};
};

//�첽����״̬
class EAsyncSendStatus
{
public:
	enum
	{
		PreSend,//׼������
		Sending,//���ڷ���
		SendCmp//�������
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

//tcp�¼��ص�����ָ��
//pEvent	tcp�����¼�
typedef void(*LPTcpEventCallback)(CTcpEvt* pEvent);

//socket�ź�����
class SocketSingalType
{
public:
	enum
	{
		Read,//�ɶ�
		Write,//��д
		Except//�쳣
	};
};

//socket�ź�����
typedef struct tagSocketSingalData
{
	SOCKET socket;//���źŵ�socket
	int singaltype;//socket�ź�����
	int sockettype;//socket����
}SocketSingalData;

//���ڴ����socket����
typedef	struct tagProcessingSocketData
{
	SOCKET socket;//���ڴ����socket
	int type;//�ź�����
}ProcessingSocketData;