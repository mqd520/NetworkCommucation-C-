#pragma once

#include <vector>
#include "TcpSession.h"

using namespace std;

namespace NetworkCommunication
{
	class CTcpSessionMgr
	{
	protected:
		vector<CTcpSession> m_vecSessionList;

	public:
		CTcpSessionMgr();
		~CTcpSessionMgr();

		void Push(CTcpSession session);
	};
}