#pragma once
#include <string>
#include <functional>
using namespace std;
using namespace std::placeholders;

namespace tc
{
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

	class TcpEvt;
	// tcp�¼��ص�����ָ��
	// pEvent	tcp�¼�����
	// pParam1	���Ӳ���1
	// pParam2	���Ӳ���2
	using LPTcpEventCallback = void(*)(TcpEvt* pEvt, void* pParam1, void* pParam2);

	// ��־�ص�����ָ��
	// type		��־����: ETcpLogType
	// log		��־����
	// pParam1	���Ӳ���1
	// pParam1	���Ӳ���2
	using LPTcpLogCallback = void(*)(ETcpLogType type, string log, void* pParam1, void* pParam2);

	// ������
	typedef struct tagPacketData
	{
		BYTE* pBuf;		// ���建����
		int nLen;		// ���建��������
		int cmd;		// ������
		int clientId;	// client id(�����ڷ����)
	}PacketData;


	// tcp�¼��ص�����ָ��
	typedef std::function<void(TcpEvt*, void*, void*)> Fun2;
}

