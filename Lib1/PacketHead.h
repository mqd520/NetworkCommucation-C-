#pragma once
#include "tc/PacketHeadBase.h"
#include "tc/NetworkStreamRead.h"
#include "tc/NetworkStreamWrite.h"

using namespace tc;

namespace lib1
{
	// ��ͷ��
	class PacketHead : public PacketHeadBase
	{
	public:
		PacketHead(int cmd = 0, int len = 0, int code = 0);
		virtual ~PacketHead();

	protected:
		INT16 nMask;		// mask, 2���ֽ�
		BYTE nCode;			// ������, 1���ֽ�

	public:
		//************************************
		// Method:    �����ж�ȡ���ݵ�����
		// Parameter: CNetworkStreamRead & ns
		//************************************
		void Read(CNetworkStreamRead& ns) override;

		//************************************
		// Method:    ������д������
		// Parameter: CNetworkStreamRead & ns
		//************************************
		void Write(CNetworkStreamWrite& ns) override;

		//************************************
		// Method:    �Ƿ����
		//************************************
		bool IsValid() override;

		//************************************
		// Method:    ��ȡ������
		//************************************
		BYTE GetCode();
	};
}