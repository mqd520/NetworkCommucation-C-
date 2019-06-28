#pragma once
#include "tc/PacketHeadBase.h"
#include "tc/NetworkStreamRead.h"
#include "tc/NetworkStreamWrite.h"

using namespace tc;

namespace lib1
{
	// 包头类
	class PacketHead : public PacketHeadBase
	{
	public:
		PacketHead(int cmd = 0, int len = 0, int code = 0);
		virtual ~PacketHead();

	protected:
		INT16 nMask;		// mask, 2个字节
		BYTE nCode;			// 加密码, 1个字节

	public:
		//************************************
		// Method:    从流中读取数据到包中
		// Parameter: CNetworkStreamRead & ns
		//************************************
		void Read(CNetworkStreamRead& ns) override;

		//************************************
		// Method:    向流中写入数据
		// Parameter: CNetworkStreamRead & ns
		//************************************
		void Write(CNetworkStreamWrite& ns) override;

		//************************************
		// Method:    是否可用
		//************************************
		bool IsValid() override;

		//************************************
		// Method:    获取加密码
		//************************************
		BYTE GetCode();
	};
}