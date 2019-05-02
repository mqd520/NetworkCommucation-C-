#pragma once
#include "TcpEvt.h"

namespace NetworkCommunication
{
	//�յ��Զ������¼�
	class CRecvPeerDataEvt : public CTcpEvt
	{
	private:
		BYTE* m_pBuf;//�յ������ݻ�����ָ��
		int m_nLen;//���ݻ���������

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ������tcp�������
		// Parameter: ���������ڽ������ݵ�socket
		//************************************
		CRecvPeerDataEvt(CTcpService* pSrv, SOCKET recv, BYTE* pBuf, int len);
		~CRecvPeerDataEvt();

		//************************************
		// Method:    ��ȡ�¼�����
		//************************************
		int GetEvtType();

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