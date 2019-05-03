#pragma once
#include "TcpEvt.h"
#include "Def.h"

namespace tc
{
	//接收客户端连接结果事件
	class CRecvConnResultEvt : public CTcpEvt
	{
	private:
		bool m_bSuccess;//连接是否成功
		TCHAR m_strClientIP[NETCOMM_MAXIPSTRELN];//客户端IP
		int m_nClientPort;//客户端端口

	public:
		CRecvConnResultEvt(CTcpService* pSrv, bool success, SOCKET client, TCHAR* ip, int port);
		~CRecvConnResultEvt();

		//************************************
		// Method:    获取事件类型
		//************************************
		int GetEvtType();

		//************************************
		// Method:    获取接收结果
		//************************************
		bool GetRecvResult();

		//************************************
		// Method:    获取客户端IP
		//************************************
		TCHAR* GetClientIP();

		//************************************
		// Method:    获取客户端端口
		//************************************
		int GetClientPort();
	};
}