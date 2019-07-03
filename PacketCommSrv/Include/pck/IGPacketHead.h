#pragma once
#include "PacketCmd.h"

#include "tc/PacketHead.h"
using namespace tc;

namespace pck
{
	// ig head
	class IGPacketHead : public PacketHead
	{
	public:
		IGPacketHead(int cmd = 0, int len = 0);

	protected:
		int nMask;		// 标记
		int nCode;		// 加密码

	public:
		//************************************
		// Method:    从流中读取数据到包中
		// Parameter: ns:	只读网络流对象
		//************************************
		virtual void Read(NetworkStreamRead& ns) override;

		//************************************
		// Method:    向流中写入数据
		// Parameter: ns:	只写网络流对象
		//************************************
		virtual void Write(NetworkStreamWrite& ns) override;

		//************************************
		// Method:    是否可用
		//************************************
		virtual bool IsValid() override;

		//************************************
		// Method:    获取code
		//************************************
		int GetCode();

		//************************************
		// Method:    获取mask
		//************************************
		int GetMask();
	};
}