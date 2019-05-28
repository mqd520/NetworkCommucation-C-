#pragma once
#include "TcpEvt.h"

namespace tc
{
	// �յ������¼�
	class RecvDataEvt : public TcpEvt
	{
	private:
		BYTE* pBuf;		// �յ������ݻ�����ָ��
		int nLen;		// ���ݻ���������

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ������tcp�������
		// Parameter: ���������ڽ������ݵ�socket
		//************************************
		RecvDataEvt(TcpService* pSrv, SOCKET recv, BYTE* pBuf, int len);
		~RecvDataEvt();

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