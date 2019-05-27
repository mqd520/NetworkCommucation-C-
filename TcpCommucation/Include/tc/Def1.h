#pragma once

#include "Include/tc/TcpEvt.h"

// tcp�¼��ص�����ָ��
// pEvent	tcp�¼�����
// pEvent	�¼����Ӳ���
typedef void(*LPTcpEventCallback)(TcpEvt* pEvt, void* pParam);

// tcp�¼�
//class ETcpEvt
//{
//public:
//	enum
//	{
//		RecvNewConnection,		// �յ�������
//		RecvPeerData,			// �յ��Զ�����
//		ConnDisconnect,			// ���ӶϿ�
//		AsyncSendDataResult,	// �첽�������ݽ��
//		RecvConnResult,			// ���տͻ������ӵĽ��
//		ConnectSrvResult,		// ���ӷ���˵Ľ��
//
//		None					// ��
//	};
//};

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