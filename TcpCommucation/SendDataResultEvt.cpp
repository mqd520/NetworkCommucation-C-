#include "stdafx.h"
#include "Include/tc/SendDataResultEvt.h"
#include "Def.h"
#include "Include/tc/Def1.h"

namespace tc
{
	SendDataResultEvt::SendDataResultEvt(TcpService* pSrv, bool success, int len, int actualLen)
		:TcpEvt(pSrv),
		bSuccess(success),
		nLen(len),
		nActualLen(actualLen)
	{
		evtType = ETcpEvtType::SendDataResult;
	}

	SendDataResultEvt::~SendDataResultEvt()
	{

	}

	bool SendDataResultEvt::GetResult()
	{
		return bSuccess;
	}

	int SendDataResultEvt::GetLen()
	{
		return nLen;
	}

	int SendDataResultEvt::GetActualLen()
	{
		return nActualLen;
	}
}