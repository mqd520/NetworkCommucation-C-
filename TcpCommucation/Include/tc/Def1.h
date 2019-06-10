#pragma once

#include <string>

using namespace std;

namespace tc
{
	// tcp�¼�����
	enum class ETcpEvt : int
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
		Info,	// ��Ϣ
		Debug,	// ����
		Err,	// ����

		None	// ����
	};

	class TcpEvt;
	// tcp�¼��ص�����ָ��
	// pEvent	tcp�¼�����
	// pParam1	���Ӳ���1
	// pParam2	���Ӳ���2
	typedef void(*LPTcpEventCallback)(TcpEvt* pEvt, void* pParam1, void* pParam2);

	// ��־�ص�����ָ��
	// type		��־����: ETcpLogType
	// log		��־����
	// pParam1	���Ӳ���1
	// pParam1	���Ӳ���2
	typedef void(*LPTcpLogCallback)(ETcpLogType type, string log, void* pParam1, void* pParam2);
}

