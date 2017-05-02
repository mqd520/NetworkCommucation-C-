#pragma once

#include "ProtocolClientMgr.h"
#include "EncryptBuffer.h"
#include "DemoPacket.h"

using namespace NetworkCommunication;

namespace DemoProtocolMgr
{
	//DemoЭ��ͻ��˹���
	class CDemoProtocolClient :public CProtocolClientMgr
	{
	public:
		CDemoProtocolClient();
		~CDemoProtocolClient();

	protected:
		CEncryptBuffer m_entrypy;//�ֽڼ��ܶ���

	protected:
		void OnBeforeSendPack(int cmd, BYTE* buf, int len);
		bool OnRecvCmpPacket(BYTE* buf, int len);
		void OnTcpConnectSuccess(TCHAR* msg);
		bool PreprocessPack(int cmd, BYTE* buf, int len);
	};
}