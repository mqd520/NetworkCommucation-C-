#pragma once
#include "TcpEvt.h"

namespace NetworkCommunication
{
	//收到对端数据事件
	class CRecvPeerDataEvt : public CTcpEvt
	{
	private:
		BYTE* m_pBuf;//收到的数据缓冲区指针
		int m_nLen;//数据缓冲区长度

	public:
		//************************************
		// Method:    构造函数
		// Parameter: 关联的tcp服务对象
		// Parameter: 关联的用于接收数据的socket
		//************************************
		CRecvPeerDataEvt(CTcpService* pSrv, SOCKET recv, BYTE* pBuf, int len);
		~CRecvPeerDataEvt();

		//************************************
		// Method:    获取事件类型
		//************************************
		int GetEvtType();

		//************************************
		// Method:    获取接收缓冲区
		//************************************
		BYTE* GetRecvBuf();

		//************************************
		// Method:    获取接收缓冲区长度
		//************************************
		int GetBufLen();
	};
}