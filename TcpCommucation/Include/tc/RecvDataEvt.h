#pragma once
#include "TcpEvt.h"

namespace tc
{
	// �յ������¼�
	class RecvDataEvt : public TcpEvt
	{
	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ������tcp�������
		// Parameter: ���������ڽ������ݵ�socket
		//************************************
		RecvDataEvt(TcpService* pSrv, SOCKET recv, BYTE* pBuf, int len);
		~RecvDataEvt();

	private:
		BYTE* pBuf;		// �յ������ݻ�����ָ��
		int nLen;		// ���ݻ���������
		string strIp;	// �Զ�ip
		int nPort;		// �Զ˶˿�

	public:
		//************************************
		// Method:    ��ȡ���ջ�����
		//************************************
		BYTE* GetRecvBuf();

		//************************************
		// Method:    ��ȡ���ջ���������
		//************************************
		int GetBufLen();

		//************************************
		// Method:    ��ȡ�Զ�ip
		//************************************
		string GetPeerIp();

		//************************************
		// Method:    ��ȡ�Զ˶˿�
		//************************************
		int GetPeerPort();
	};
}