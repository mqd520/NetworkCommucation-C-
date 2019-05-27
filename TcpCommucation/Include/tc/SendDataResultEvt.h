#pragma once
#include "TcpEvt.h"

namespace tc
{
	// �������ݽ���¼�
	class SendDataResultEvt : public TcpEvt
	{
	private:
		bool bSuccess;	// �����Ƿ�ɹ�
		int nLen;		// Ԥ�Ʒ��ͳ���
		int nActualLen;	// ʵ�ʷ��ͳ���

	public:
		SendDataResultEvt(CTcpService* pSrv, bool success, int len, int actualLen);
		~SendDataResultEvt();

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