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
		// Parameter: �Զ�socket
		// Parameter: BYTE * pBuf:	������
		// Parameter: int len:		����������
		//************************************
		RecvPeerDataEvt(TcpService* pSrv, SOCKET recv, BYTE* pBuf, int len);
		~RecvPeerDataEvt();

	private:
		BYTE* pBuf;		// �յ������ݻ�����ָ��
		int nLen;		// ���ݻ���������

	public:
		//************************************
		// Method:    ��ȡ���ջ�����
		//************************************
		BYTE* GetRecvBuf();

		//************************************
		// Method:    ��ȡ���ջ���������
		//************************************
		int GetBufLen();
	};
}