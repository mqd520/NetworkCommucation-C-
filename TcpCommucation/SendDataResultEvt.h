#pragma once
#include "TcpEvt.h"

namespace NetworkCommunication
{
	//����(�첽)���ݽ���¼�
	class CSendDataResultEvt : public CTcpEvt
	{
	private:
		bool m_bSuccess;//�����Ƿ�ɹ�
		int m_nLen;//Ԥ�Ʒ��ͳ���
		int m_nActualLen;//ʵ�ʷ��ͳ���

	public:
		CSendDataResultEvt(CTcpService* pSrv, bool success, int len, int actualLen);
		~CSendDataResultEvt();

		//************************************
		// Method:    ��ȡ�¼�����
		//************************************
		int GetEvtType();

		//************************************
		// Method:    ��ȡ���ͽ��
		//************************************
		bool GetResult();

		//************************************
		// Method:    ��ȡԤ�Ʒ��ͳ���
		//************************************
		int GetLen();

		//************************************
		// Method:    ��ȡʵ�ʷ��ͳ���
		//************************************
		int GetActualLen();
	};
}