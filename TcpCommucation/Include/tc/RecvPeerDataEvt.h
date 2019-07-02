#pragma once
#include "TcpEvt.h"

namespace tc
{
	// �յ��Զ������¼�
	class RecvPeerDataEvt : public TcpEvt
	{
	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ������tcp�������
		// Parameter: ���������ڽ������ݵ�socket
		//************************************
		RecvPeerDataEvt(TcpService* pSrv, SOCKET recv, BYTE* pBuf, int len);
		~RecvPeerDataEvt();

	private:
		BYTE* pBuf;		// �յ������ݻ�����ָ��
		int nLen;		// ���ݻ���������
		//string strIp;	// �Զ�ip
		//int nPort;		// �Զ˶˿�

	public:
		//************************************
		// Method:    ��ȡ���ջ�����
		//************************************
		BYTE* GetRecvBuf();

		//************************************
		// Method:    ��ȡ���ջ���������
		//************************************
		int GetBufLen();

		////************************************
		//// Method:    ��ȡ�Զ�ip
		////************************************
		//string GetPeerIp();

		////************************************
		//// Method:    ��ȡ�Զ˶˿�
		////************************************
		//int GetPeerPort();
	};
}