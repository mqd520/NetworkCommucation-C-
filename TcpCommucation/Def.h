#pragma once
#include <vector>
#include "SocketAPI.h"

using namespace std;
using namespace tc;

#define	TC_MAXCLIENTCOUNT			65535	//���tcp������
#define TC_TCPRECVBUFFERSIZE		1024	//tcp���ջ�����Ĭ�ϴ�С
#define TC_TCPSENDBUFFERSIZE		1024	//tcp�첽���ͻ�����Ĭ�ϴ�С
#define TC_MAXIPSTRELN				20		//ip�ַ�����󳤶�

// �����ַ
typedef struct tagNetAddress
{
	TCHAR ip[TC_MAXIPSTRELN];	// ip
	int port;					// �˿�
}NetAddress;

// select����socket����
class ESelectSocketType
{
public:
	enum
	{
		Accept,			// ���������ӵķ����socket
		ReadWriteData,	// ��д���ݵ�socket
		Connect			// ���ӷ���˵Ŀͻ���socket
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

// select����socket���ݽṹ
typedef struct tagSelectSocketData
{
	SOCKET	socket;	// socket
	int type;		// socket����: ESelectSocketType
}SelectSocketData;

// ��Զ˷������ݽ��
typedef struct tagSendPeerDataResult
{
	TCHAR ip[20];	//�Զ�IP
	int port;		//�Զ˶˿�
	bool success;	//�Ƿ�ɹ�
	int len;		//���������ֽڳ���
	int actualLen;	//ʵ�ʷ����ֽڳ���
}SendPeerDataResult;

// socket�ź�����
class ESocketSingalType
{
public:
	enum
	{
		Read,	// �ɶ�
		Write,	// ��д
		Except	// �쳣
	};
};

// socket�ź�����
typedef struct tagSocketSingalData
{
	SOCKET socket;	// ���źŵ�socket
	int singaltype;	// socket�ź�����: ESocketSingalType
	int sockettype;	// socket����:	ESelectSocketType
}SocketSingalData;

// ���ڴ����socket����
typedef	struct tagProcessingSocketData
{
	SOCKET socket;	// ���ڴ����socket
	int type;		// �ź�����: ESelectSocketType
}ProcessingSocketData;