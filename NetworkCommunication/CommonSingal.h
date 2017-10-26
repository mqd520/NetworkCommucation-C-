#pragma once
#include "SocketSingal.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	//�������źŴ���
	class CCommonSingal : public CSocketSingal
	{
	private:
		CSocketAPI m_socketAPI;//socket api

	protected:
		//************************************
		// Method:    ����socket�ɶ��ź�
		// Parameter: socket
		// Parameter: socket����
		//************************************
		void ProcessReadSingal(SOCKET socket, int type);

		//************************************
		// Method:    ����socket��д�ź�
		// Parameter: socket
		// Parameter: socket����
		//************************************
		void ProcessWriteSingal(SOCKET socket, int type);

		//************************************
		// Method:    ����socket�쳣�ź�
		// Parameter: socket
		// Parameter: socket����
		//************************************
		void ProcessExceptSingal(SOCKET socket, int type);

		//************************************
		// Method:    �յ��������¼�����
		// Parameter: socket
		//************************************
		void OnRecvNewConn(SOCKET socket);

	public:
		CCommonSingal();
		~CCommonSingal();
	};
}