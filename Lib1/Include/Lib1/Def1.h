#pragma once

namespace lib1
{
	// ��������
	enum class EServiceType : int
	{
		PlazaSrv = 3,			// ��������
		CenterSrv = 5,			// ���ķ���

		None = -1				// None
	};

	// ������
	typedef struct tagPacketData
	{
		BYTE* pBuf;		// ���建����
		int nLen;		// ���建��������
		int cmd;		// ������
		int clientId;	// client id(�����ڷ����)
	}PacketData;
}