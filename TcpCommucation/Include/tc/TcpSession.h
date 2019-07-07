#pragma once

#include <string>
using namespace std;

namespace tc
{
	// tcp session
	class TcpSession
	{
	public:
		//************************************
		// Method:    ¹¹Ôìº¯Êý
		// Parameter: string peerIp
		// Parameter: int peerPort
		// Parameter: int clientId
		// Parameter: string localIp
		// Parameter: int localPort
		//************************************
		TcpSession(string peerIp = "", int peerPort = 0, int clientId = 0, string localIp = "", int localPort = 0);
		virtual ~TcpSession();

	public:
		string strPeerIp;		// peer ip
		int nPeerPort;			// peer port

		string strLocalIp;		// local ip
		int nLocalPort;			// local port

		int nClientId;			// client id
	};
}