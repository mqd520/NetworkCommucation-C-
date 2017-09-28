#pragma once
#include <queue>
#include "TcpEvt.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp�¼��������
	class CTcpEvtMgr
	{
	private:
		queue<CTcpEvt*> m_queueEvent;//tcp�¼�����

	public:
		CTcpEvtMgr();
		~CTcpEvtMgr();

		//************************************
		// Method:    tcp�¼������Ƿ�Ϊ��
		//************************************
		bool IsEmpty();

		//************************************
		// Method:    ׷��һ��tcp�����¼�
		// Parameter: tcp�����¼�
		//************************************
		void PushTcpEvent(CTcpEvt* pEvent);

		//************************************
		// Method:    ����tcp�¼�
		//************************************
		void ProcessTcpEvt();
	};
}