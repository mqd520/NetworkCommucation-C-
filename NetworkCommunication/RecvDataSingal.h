#pragma once
#include "SocketSingal.h"

namespace NetworkCommunication
{
	//�������źŴ���
	class CRecvDataSingal : public CSocketSingal 
	{
	protected:
		//************************************
		// Method:    ����socket�ɶ��ź�
		// Parameter: socket
		// Parameter: socket����
		//************************************
		void ProcessReadSingal(SOCKET socket, int type);

	public:
		CRecvDataSingal();
		~CRecvDataSingal();
	};
}