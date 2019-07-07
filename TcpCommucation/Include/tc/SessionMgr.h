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

	protected:
		vector<TcpSession*> vecSessions;	// session list

	public:
		virtual TcpSession* CreateSession();

		virtual void Add(TcpSession* pData);

		virtual TcpSession* Add(string peerIp = "", int peerPort = 0, int clientId = 0, string localIp = "", int localPort = 0);

		virtual TcpSession Remove(int clientId);

		virtual TcpSession Remove(string peerIp, int peerPort);

		virtual void Remove();

		virtual TcpSession Get(int clientId);

		virtual TcpSession Get(string peerIp, int peerPort);

		virtual TcpSession* Get1(int clientId);

		virtual TcpSession* Get1(string peerIp, int peerPort);

		virtual void GetAllClientId(vector<int>& vec);
	};
}