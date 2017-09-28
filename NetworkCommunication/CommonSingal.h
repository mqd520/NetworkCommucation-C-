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
		// Method:    �յ��������¼�����
		// Parameter: socket
		//************************************
		void OnRecvNewConn(SOCKET socket);

	public:
		CCommonSingal();
		~CCommonSingal();
	};
}