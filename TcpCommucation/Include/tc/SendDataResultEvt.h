#pragma once
#include "TcpEvt.h"

namespace tc
{
	// 发送数据结果事件
	class SendDataResultEvt : public TcpEvt
	{
	private:
		bool bSuccess;	// 发送是否成功
		int nLen;		// 预计发送长度
		int nActualLen;	// 实际发送长度

	public:
		SendDataResultEvt(CTcpService* pSrv, bool success, int len, int actualLen);
		~SendDataResultEvt();

		//************************************
		// Method:    获取发送结果
		//************************************
		bool GetResult();

		//************************************
		// Method:    获取预计发送长度
		//************************************
		int GetLen();

		//************************************
		// Method:    获取实际发送长度
		//************************************
		int GetActualLen();
	};
}