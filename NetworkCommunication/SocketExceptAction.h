#pragma once
#include "TcpAction.h"

namespace NetworkCommunication
{
	//socket异常动作
	class CSocketExcept : public CTcpAction
	{
	private:
		int m_nSocketType;//socket类型

	public:
		CSocketExcept(SOCKET socket, int type);
		~CSocketExcept();

		//************************************
		// Method:    获取tcp动作类型
		//************************************
		int GetActionType();

		//************************************
		// Method:    获取异常的socket类型
		//************************************
		int GetExceptSocketType();
	};
}