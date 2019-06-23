#pragma once
#include <queue>
#include "SocketEvt.h"

using namespace std;

namespace tc
{
	// �����ݴ�������
	class RecvDataHandler
	{
	public:
		RecvDataHandler();
		~RecvDataHandler();

	private:
		queue<SocketEvt*> quSocketEvts;	// socket�¼�����

	private:
		//************************************
		// Method:    �յ��������¼�����
		//************************************
		void OnRecvNewConn(SocketEvt* pEvt);

		//************************************
		// Method:    �յ��Զ������¼�����
		//************************************
		void OnRecvPeerData(SocketEvt* pEvt);

		//************************************
		// Method:    ���ӶϿ��¼�����
		//************************************
		void OnConnDisconnect(SocketEvt* pEvt);

	public:
		void PushSocketEvt(SocketEvt* pEvt);

		//************************************
		// Method:    socket�¼������Ƿ�Ϊ��
		//************************************
		bool IsEmpty();

		//************************************
		// Method:    ���socket�¼�����
		//************************************
		void Clear();

		//************************************
		// Method:    ����socket�¼�����
		//************************************
		void ProcessSocketEvt();
	};
}