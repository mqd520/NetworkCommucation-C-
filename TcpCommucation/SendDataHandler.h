#pragma once
#include "SocketDataHandler.h"

namespace tc
{
	// 发数据处理类
	class SendDataHandler : public SocketDataHandler
	{
	public:
		SendDataHandler();
		~SendDataHandler();

	private:
		//************************************
		// Method:    发送对端数据事件处理
		//************************************
		void OnSendPeerData(SocketEvt* pEvt);

	protected:
		//************************************
		// Method:    socket事件处理
		//************************************
		virtual void OnSocketEvtProcess(SocketEvt* pEvt) override;
	};
}