#pragma once
#include "SocketDataHandler.h"

namespace tc
{
	// 收数据处理器类
	class RecvDataHandler : public SocketDataHandler
	{
	public:
		RecvDataHandler();
		~RecvDataHandler();

	private:
		//************************************
		// Method:    收到新连接事件处理
		//************************************
		void OnRecvNewConn(SocketEvt* pEvt);

		//************************************
		// Method:    收到对端数据事件处理
		//************************************
		void OnRecvPeerData(SocketEvt* pEvt);

		//************************************
		// Method:    连接断开事件处理
		//************************************
		void OnConnDisconnect(SocketEvt* pEvt);

		//************************************
		// Method:    连接服务端完成事件处理
		//************************************
		void OnConnectCpl(SocketEvt* pEvt);

	protected:
		//************************************
		// Method:    socket事件处理
		//************************************
		virtual void OnSocketEvtProcess(SocketEvt* pEvt) override;
	};
}