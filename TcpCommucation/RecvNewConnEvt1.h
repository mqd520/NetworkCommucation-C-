#pragma once
#include "TcpEvt.h"
#include "TcpService.h"

namespace tc
{
	//�յ��������¼�
	class CRecvNewConnEvt : public TcpEvt
	{
	public:
		bool m_bRefuse;//�û��Ƿ�ܾ���������

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ������tcp�������
		// Parameter: �����Ŀͻ���socket
		//************************************
		CRecvNewConnEvt(CTcpService* pSrv, SOCKET client);
		~CRecvNewConnEvt();

		//************************************
		// Method:    ��ȡ�¼�����
		//************************************
		int GetEvtType();
	};
}