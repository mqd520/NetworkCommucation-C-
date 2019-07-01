#include "stdafx.h"
#include "Include/tc/RecvNewConnSocEvt.h"

namespace tc
{
	RecvNewConnSocEvt::RecvNewConnSocEvt(SOCKET server, vector<SOCKET>& clients)
	{
		this->evtType = ESocketEvtType::RecvNewConn;
		this->server = server;
		this->vecClients = clients;
	}

	RecvNewConnSocEvt::~RecvNewConnSocEvt()
	{

	}

	SOCKET RecvNewConnSocEvt::GetServerSocket() const
	{
		return server;
	}

	vector<SOCKET> RecvNewConnSocEvt::GetClients()
	{
		vector<SOCKET> vec;

		for (vector<SOCKET>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
		{
			vec.push_back(*it);
		}

		return vec;
	}
}