#pragma once
#include <queue>
#include "Include/tc/TcpEvt.h"

using namespace std;

namespace tc
{
	//tcp�¼��������
	class CTcpEvtMgr
	{
	private:
		queue<TcpEvt*> m_queueEvent;//tcp�¼�����

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
		void PushTcpEvent(TcpEvt* pEvent);

		//************************************
		// Method:    ����tcp�¼�
		//************************************
		void ProcessTcpEvt();
	};
}