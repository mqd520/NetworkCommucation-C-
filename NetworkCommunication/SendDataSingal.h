#pragma once
#include "SocketSingal.h"

namespace NetworkCommunication
{
	//�������źŴ���
	class CSendDataSingal : public CSocketSingal
	{
	protected:
		//************************************
		// Method:    ����socket��д�ź�
		// Parameter: socket
		// Parameter: socket����
		//************************************
		void ProcessWriteSingal(SOCKET socket, int type);

	public:
		CSendDataSingal();
		~CSendDataSingal();
	};
}