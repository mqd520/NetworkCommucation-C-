#pragma once
#include "TcpClient.h"

namespace tc
{
	// ���ڰ���ͨ�ŷ���ͻ���
	class PacketClient : public TcpClient
	{
	public:
		PacketClient(string ip = "", int port = 0);

	//protected:
	//	//************************************
	//	// Method:    �յ�tcp�¼�����
	//	// Parameter: pEvt: tcp�¼�
	//	//************************************
	//	virtual void OnTcpEvt(TcpEvt* pEvt) override;

	//public:
	//	//************************************
	//	// Method:    ����
	//	// Parameter: Packet & pck:	������
	//	//************************************
	//	virtual void SendPck(Packet& pck);
	};
}