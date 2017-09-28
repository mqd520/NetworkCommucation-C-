#pragma once
#include <queue>
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	//socket�źŴ���
	class CSocketSingal
	{
	protected:
		queue<SocketSingalData> m_queueSocketData;//���źŵ�socket���ݶ���

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