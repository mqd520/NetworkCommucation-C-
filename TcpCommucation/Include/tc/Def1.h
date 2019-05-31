#pragma once

#include "TcpEvt.h"

using namespace tc;

// tcp�¼�
enum ETcpEvt
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
enum ELogType
{
	Info,	// ��Ϣ
	Debug,	// ����
	Err,	// ����

	None1	// ����
};


// tcp�¼��ص�����ָ��
// pEvent	tcp�¼�����
// pEvent	�¼����Ӳ���
typedef void(*LPTcpEventCallback)(TcpEvt* pEvt, void* pParam);

// ��־�ص�����ָ��
// type		��־����: ELogType
// log		��־����
// pParam1	���Ӳ���1
// pParam1	���Ӳ���2
typedef void(*LPLogCallback)(int type, string log, void* pParam1, void* pParam2);