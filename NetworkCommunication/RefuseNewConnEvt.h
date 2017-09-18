#pragma once
#include "Def.h"
#include "TcpSrvEvt.h"

namespace NetworkCommunication
{
	//�ܾ������¼�
	class CRefuseNewConnEvt : public CTcpSrvEvt
	{
	private:
		TCHAR m_strIP[MAXIPSTRELN];//�ͻ���IP
		int m_nPort;//�ͻ��˶˿�

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ������tcp�������
		// Parameter: �����Ŀͻ���socket
		// Parameter: �ͻ���IP
		// Parameter: �ͻ��˶˿�
		//************************************
		CRefuseNewConnEvt(CTcpService* pSrv, SOCKET client, TCHAR* ip, int port);
		~CRefuseNewConnEvt();

		//************************************
		// Method:    ��ȡ�¼�����
		//************************************
		int GetEvtType();

		//************************************
		// Method:    ��ȡ�ͻ���IP
		//************************************
		TCHAR* GetClientIP();

		//************************************
		// Method:    ��ȡ�ͻ��˶˿�
		//************************************
		int GetClientPort();
	};
}