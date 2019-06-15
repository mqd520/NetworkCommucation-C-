#pragma once
#include <queue>
#include "Def.h"
#include "Include/tc/SocketTool.h"
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// select�źŴ�����
	class SelectSingal
	{
	protected:
		queue<SocketSingalData> quSockets;		// ���źŵ�socket���ݶ���
		//vector<SocketSingalData> vecSockets;	// ���źŵ�socket���ݼ���
		CThreadLock lock1;						// �߳���, ���: quSignalSocketData

	protected:
		//************************************
		// Method:    ����������
		// Parameter: �����socket
		//************************************
		void RecvNewConnection(SOCKET socket);

		//************************************
		// Method:    ���նԶ�����
		// Parameter: �շ����ݵ�socket
		//************************************
		void RecvPeerData(SOCKET socket);

		//************************************
		// Method:    ��������
		// Parameter: �շ����ݵ�socket
		//************************************
		void SendData(SOCKET socket);

		//************************************
		// Method:    ���ӷ���˳ɹ��¼�����
		// Parameter: �ͻ���socket
		//************************************
		void OnConnectSuccess(SOCKET socket);

		//************************************
		// Method:    ���ӷ����ʧ���¼�����
		// Parameter: �ͻ���socket
		//************************************
		void OnConnectFail(SOCKET socket);

	public:
		SelectSingal();
		~SelectSingal();

		//************************************
		// Method:    ����һ��socket�ź�����
		// Parameter: socket�ź�����
		//************************************
		void PushSocketSingal(SocketSingalData data);

		//************************************
		// Method:    ����socket�ź�
		//************************************
		void ProcessSocketSingal();

		//************************************
		// Method:    �ȴ������socket�����Ƿ�Ϊ��
		//************************************
		bool IsEmpty();
	};
}