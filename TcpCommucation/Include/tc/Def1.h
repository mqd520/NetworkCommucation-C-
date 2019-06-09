#pragma once

#include "TcpEvt.h"

using namespace tc;

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

// tcp�¼��ص�����ָ��
// pEvent	tcp�¼�����
// pParam1	���Ӳ���1
// pParam2	���Ӳ���2
typedef void(*LPTcpEventCallback)(TcpEvt* pEvt, void* pParam1, void* pParam2);

// ��־�ص�����ָ��
// type		��־����: ELogType
// log		��־����
// pParam1	���Ӳ���1
// pParam1	���Ӳ���2
typedef void(*LPLogCallback)(int type, string log, void* pParam1, void* pParam2);