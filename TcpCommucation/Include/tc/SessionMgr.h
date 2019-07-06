#pragma once

#include <vector>
using namespace std;

#include "TcpSession.h"

namespace tc
{
	// session mgr
	class SessionMgr
	{
	public:
		SessionMgr();
		virtual ~SessionMgr();

	private:
		vector<TcpSession> vecSessionDatas;	// session data list

	public:
		virtual bool IsEqual(const TcpSession& obj1, const TcpSession& obj2);

		virtual void Add(TcpSession& data);

		virtual TcpSession Remove(int clientId);

		virtual TcpSession Remove(string peerIp, int peerPort);

		virtual void Remove(TcpSession& data);

		virtual void Remove();

		virtual TcpSession Get(int clientId);

		virtual TcpSession Get(string peerIp, int peerPort);

		virtual void Get(vector<TcpSession>& vec);
	};
}