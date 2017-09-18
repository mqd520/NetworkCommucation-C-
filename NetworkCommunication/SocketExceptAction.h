#pragma once
#include "TcpAction.h"

namespace NetworkCommunication
{
	//socket�쳣����
	class CSocketExcept : public CTcpAction
	{
	private:
		int m_nSocketType;//socket����

	public:
		CSocketExcept(SOCKET socket, int type);
		~CSocketExcept();

		//************************************
		// Method:    ��ȡtcp��������
		//************************************
		int GetActionType();

		//************************************
		// Method:    ��ȡ�쳣��socket����
		//************************************
		int GetExceptSocketType();
	};
}