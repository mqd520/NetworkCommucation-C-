#pragma once

#include "Include/tc/TcpEvt.h"

// tcp�¼��ص�����ָ��
// pEvent	tcp�¼�����
// pEvent	�¼����Ӳ���
typedef void(*LPTcpEventCallback)(TcpEvt* pEvt, void* pParam);

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