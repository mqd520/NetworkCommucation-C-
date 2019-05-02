#include "stdafx.h"
#include "SendDataResultEvt.h"
#include "Def.h"

namespace NetworkCommunication
{
	CSendDataResultEvt::CSendDataResultEvt(CTcpService* pSrv, bool success, int len, int actualLen)
		:CTcpEvt(pSrv),
		m_bSuccess(success),
		m_nLen(len),
		m_nActualLen(actualLen)
	{

	}

	CSendDataResultEvt::~CSendDataResultEvt()
	{

	}

	int CSendDataResultEvt::GetEvtType()
	{
		return ETcpEvent::AsyncSendDataResult;
	}

	bool CSendDataResultEvt::GetResult()
	{
		return m_bSuccess;
	}

	int CSendDataResultEvt::GetLen()
	{
		return m_nLen;
	}

	int CSendDataResultEvt::GetActualLen()
	{
		return m_nActualLen;
	}
}