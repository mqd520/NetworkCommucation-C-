#pragma once
#include <queue>
#include "Def.h"
#include "SocketAPI.h"

using namespace std;

namespace NetworkCommunication
{
	//socket�źŴ���
	class CSocketSingal
	{
	protected:
		queue<SocketSingalData> m_queueSocketData;//���źŵ�socket���ݶ���
		CSocketAPI m_socketAPI;//

	protected:
		//************************************
		// Method:    ����socket�ɶ��ź�
		// Parameter: socket
		// Parameter: socket����
		//************************************
		virtual void ProcessReadSingal(SOCKET socket, int type);

		//************************************
		// Method:    ����socket��д�ź�
		// Parameter: socket
		// Parameter: socket����
		//************************************
		virtual void ProcessWriteSingal(SOCKET socket, int type);

		//************************************
		// Method:    ����socket�쳣�ź�
		// Parameter: socket
		// Parameter: socket����
		//************************************
		virtual void ProcessExceptSingal(SOCKET socket, int type);

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
		CSocketSingal();
		~CSocketSingal();

		//************************************
		// Method:    ����һ��socket�ź�����
		// Parameter: socket�ź�����
		//************************************
		void PushSocket(SocketSingalData data);

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