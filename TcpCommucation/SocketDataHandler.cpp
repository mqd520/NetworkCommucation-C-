#include "stdafx.h"
#include "SocketDataHandler.h"

namespace tc
{
	SocketDataHandler::SocketDataHandler()
	{

	}

	SocketDataHandler::~SocketDataHandler()
	{
		Clear();
	}

	void SocketDataHandler::PushSocketEvt(SocketEvt* pEvt)
	{
		quSocketEvts.push(pEvt);
	}

	bool SocketDataHandler::IsEmpty()
	{
		return quSocketEvts.empty();
	}

	void SocketDataHandler::Clear()
	{
		while (!quSocketEvts.empty())
		{
			SocketEvt* pEvt = quSocketEvts.front();
			quSocketEvts.pop();
			delete pEvt;
		}
	}

	void SocketDataHandler::ProcessSocketEvt()
	{
		while (!quSocketEvts.empty())
		{
			SocketEvt* pEvt = quSocketEvts.front();
			quSocketEvts.pop();
			OnSocketEvtProcess(pEvt);

			delete pEvt;
		}
	}

	void SocketDataHandler::OnSocketEvtProcess(SocketEvt* pEvt)
	{

	}
}