#pragma once
#include "Def.h"
#include "TcpEvt.h"

namespace NetworkCommunication
{
	//拒绝连接事件
	class CRefuseNewConnEvt : public CTcpEvt
	{
	private:
		TCHAR m_strIP[NETCOMM_MAXIPSTRELN];//客户端IP
		int m_nPort;//客户端端口

	public:
		//************************************
		// Method:    构造函数
		// Parameter: 关联的tcp服务对象
		// Parameter: 关联的客户端socket
		// Parameter: 客户端IP
		// Parameter: 客户端端口
		//************************************
		CRefuseNewConnEvt(CTcpService* pSrv, SOCKET client, TCHAR* ip, int port);
		~CRefuseNewConnEvt();

		//************************************
		// Method:    获取事件类型
		//************************************
		int GetEvtType();

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