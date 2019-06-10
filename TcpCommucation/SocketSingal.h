#pragma once
#include <queue>
#include "Def.h"
#include "Include/tc/SocketTool.h"

using namespace std;

namespace tc
{
	// socket�źŴ�����
	class SocketSingalProcess
	{
	protected:
		queue<SocketSingalData> quSignalSocketData;	// ���źŵ�socket���ݶ���

	protected:
		//************************************
		// Method:    ����socket�ɶ��ź�
		// Parameter: socket
		// Parameter: socket����: ESocketType
		//************************************
		virtual void ProcessReadSingal(SOCKET socket, ESocketType type);

		//************************************
		// Method:    ����socket��д�ź�
		// Parameter: socket
		// Parameter: socket����: ESocketType
		//************************************
		virtual void ProcessWriteSingal(SOCKET socket, ESocketType type);

		//************************************
		// Method:    ����socket�쳣�ź�
		// Parameter: socket
		// Parameter: socket����: ESocketType
		//************************************
		virtual void ProcessExceptSingal(SOCKET socket, ESocketType type);

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
		SocketSingalProcess();
		~SocketSingalProcess();

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