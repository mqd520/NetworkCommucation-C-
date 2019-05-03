#pragma once
#include "TcpEvt.h"
#include "Def.h"

namespace tc
{
	//���տͻ������ӽ���¼�
	class CRecvConnResultEvt : public CTcpEvt
	{
	private:
		bool m_bSuccess;//�����Ƿ�ɹ�
		TCHAR m_strClientIP[NETCOMM_MAXIPSTRELN];//�ͻ���IP
		int m_nClientPort;//�ͻ��˶˿�

	public:
		CRecvConnResultEvt(CTcpService* pSrv, bool success, SOCKET client, TCHAR* ip, int port);
		~CRecvConnResultEvt();

		//************************************
		// Method:    ��ȡ�¼�����
		//************************************
		int GetEvtType();

		//************************************
		// Method:    ��ȡ���ս��
		//************************************
		bool GetRecvResult();

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