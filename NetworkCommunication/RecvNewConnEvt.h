#pragma once
#include "TcpSrvEvt.h"
#include "TcpService.h"

namespace NetworkCommunication
{
	//�յ��������¼�
	class CRecvNewConnEvt : public CTcpSrvEvt
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