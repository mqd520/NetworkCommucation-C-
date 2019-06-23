#pragma once
#include <vector>
#include <WinSock2.h>

using namespace std;

#define	TC_MAXCLIENTCOUNT			65535	//���tcp������
#define TC_TCPRECVBUFFERSIZE		1024	//tcp���ջ�����Ĭ�ϴ�С
#define TC_TCPSENDBUFFERSIZE		1024	//tcp�첽���ͻ�����Ĭ�ϴ�С
#define TC_MAXIPSTRELN				20		//ip�ַ�����󳤶�

namespace tc
{
	// socket����
	enum class ESocketType : int
	{
		Accept,			// ���ڽ���������(����˵�socket)
		SendRecvData,	// ������(��)���ݵ�socket
		Connect			// �������ӷ���˵�socket(�ͻ��˵�socket)
	};

	// �첽����״̬
	enum class EAsyncSendStatus : int
	{
		PreSend,	// ׼������
		Sending,	// ���ڷ���
		SendCmp		// �������
	};

	// socket�ź�����
	enum class ESocketSingalType : int
	{
		Read,	// �ɶ�
		Write,	// ��д
		Except	// �쳣
	};

	// socket�¼�����
	enum class ESocketEvtType : int
	{
		RecvNewConn,		// �յ�������
		RecvPeerData,		// �յ��Զ�����
		ConnDisconnect,		// ���ӱ��Ͽ�
		
		None				// ��
	};

	// �����ַ
	typedef struct tagNetAddress
	{
		string ip;	// ip
		int port;	// �˿�
	}NetAddress;

	// select����socket���ݽṹ
	typedef struct tagSelectSocketData
	{
		SOCKET	socket;		// socket
		ESocketType type;	// socket����: ESocketType
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
	typedef struct tagSocketSingalData
	{
		SOCKET socket;					// ���źŵ�socket
		ESocketSingalType singaltype;	// socket�ź�����: ESocketSingalType
		ESocketType sockettype;			// socket����:	ESocketType
	}SocketSingalData;

	// ���ڴ����socket����
	typedef	struct tagProcessingSocketData
	{
		SOCKET socket;			// ���ڴ����socket
		ESocketSingalType type;	// �ź�����: ESocketType
	}ProcessingSocketData;

	// socket��Ϣ����
	typedef struct tagSocketInfoData
	{
		SOCKET socket;		// ������socket
		ESocketType type;	// socket type
		string peerIp;		// �Զ�ip
		int peerPort;		// �Զ˶˿�
		string localIP;		// �����ı���ip
		int localPort;		// �����ı��ض˿�
		int socketId;		// socket id, ����һ��socket
	}SocketInfoData;
}

