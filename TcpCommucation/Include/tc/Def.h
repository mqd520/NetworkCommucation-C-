#pragma once
#include <vector>
#include <WinSock2.h>
#include <functional>
using namespace std;
using namespace std::placeholders;

#define	TC_MAXCLIENTCOUNT			65535	// ���tcp������
#define TC_TCPRECVBUFFERSIZE		4096	// tcp���ջ�����Ĭ�ϴ�С
#define TC_RECONNECTTIME			3000	// �Զ��������ʱ��

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
		SendPeerData,		// ���ͶԶ�����
		ConnectCpl,			// ���ӷ�������

		None				// ��
	};

	// tcp srv ����
	enum class ETcpSrvType : int
	{
		Server,		// �����
		Client,		// �ͻ���

		None		// ��
	};

	// tcp�¼�����
	enum class ETcpEvtType : int
	{
		RecvNewConn,		// �յ�������
		RecvData,			// �յ��Զ�����
		ConnDisconnect,		// ���ӶϿ�
		SendDataResult,		// �������ݽ��
		RecvConnResult,		// ���տͻ������ӵĽ��
		ConnectSrvResult,	// ���ӷ���˵Ľ��

		None				// ��
	};

	// ��־����
	enum class ETcpLogType : int
	{
		Info,		// ��Ϣ
		Warn,		// ����
		Debug,		// ����
		Error,		// ����
		Fatal,		// ���ش���
		Exception,	// ϵͳ�쳣

		None	// ��
	};

	// ���ӶϿ�ԭ��
	enum class EDisconnReason
	{
		Peer,			// �Է��ر�
		Local,			// ���عر�
		Error,			// ����socket����

		Other			// ����ԭ��
	};

	// ������
	typedef struct tagPacketData
	{
		BYTE* pBuf;		// ���建����
		int nLen;		// ���建��������
		int cmd;		// ������
		int clientId;	// client id(�����ڷ����)
	}PacketData;

	class TcpEvt;
	// tcp�¼��ص�����ָ��
	typedef std::function<void(TcpEvt*, void*, void*)> Fun2;

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

