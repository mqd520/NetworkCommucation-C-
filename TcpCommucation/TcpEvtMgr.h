#pragma once
#include <queue>
#include "Include/tc/TcpEvt.h"

using namespace std;

namespace tc
{
	// tcp�¼�������
	class TcpEvtMgr
	{
	private:
		queue<TcpEvt*> queueEvent;	// tcp�¼�����

	public:
		TcpEvtMgr();
		~TcpEvtMgr();

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