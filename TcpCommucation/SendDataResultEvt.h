#pragma once
#include "TcpEvt.h"

namespace NetworkCommunication
{
	//发送(异步)数据结果事件
	class CSendDataResultEvt : public CTcpEvt
	{
	private:
		bool m_bSuccess;//发送是否成功
		int m_nLen;//预计发送长度
		int m_nActualLen;//实际发送长度

	public:
		CSendDataResultEvt(CTcpService* pSrv, bool success, int len, int actualLen);
		~CSendDataResultEvt();

		//************************************
		// Method:    获取事件类型
		//************************************
		int GetEvtType();

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