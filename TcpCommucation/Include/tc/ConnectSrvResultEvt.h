#pragma once
#include "TcpEvt.h"

namespace tc
{
	class ConnectSrvResultEvt : public TcpEvt
	{
	private:
		bool bSuccess;

	public:
		ConnectSrvResultEvt(TcpService* pSrv, bool success);
		~ConnectSrvResultEvt();

		bool GetConnectResult();
	};
}