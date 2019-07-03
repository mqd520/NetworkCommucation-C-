#pragma once
#include "Def.h"
#include "IGPacketSrv.h"

#include "tc/PacketClient.h"
#include "tc/KeepAliveClient.h"
using namespace tc;

namespace pck
{
	// ig��ͨ�ŷ���
	class IGPacketSrvClient : public PacketClient, public IGPacketSrv, public KeepAliveClient
	{
	public:
		//************************************
		// Method:    ���캯��
		// Parameter: EServerType localType:	���ط���������
		// Parameter: EServerType peerType:		�Զ˷���������
		// Parameter: string ip:	ip
		// Parameter: int port:		port
		// Parameter: bool bSendPwd:	�Ƿ���Ҫ�����˷�������
		//************************************
		IGPacketSrvClient(
			EServerType localType = EServerType::None, EServerType peerType = EServerType::None,
			string ip = "", int port = 0,
			bool bSendPwd = true);
		~IGPacketSrvClient();

	protected:
		bool bSendPwd;			// �Ƿ���Ҫ�����˷�������

	protected:
		//************************************
		// Method:    ���ӷ��������¼�����
		// Parameter: pEvt: tcp�¼�
		//************************************
		virtual void OnConnectSrvCpl(ConnectSrvCplEvt* pEvt) override;

		//************************************
		// Method:    �յ��Զ������¼�����
		// Parameter: pEvt: tcp�¼�
		//************************************
		virtual void OnRecvPeerData(RecvPeerDataEvt* pEvt) override;

		//************************************
		// Method:    ���ӶϿ��¼�����
		// Parameter: pEvt: tcp�¼�
		//************************************
		virtual void OnConnDisconnect(ConnDisconnectEvt* pEvt) override;

		//************************************
		// Method:    Ԥ�������
		// Parameter: data:	������
		//************************************
		virtual void PreProcessPck(PacketData& data) override;

		//************************************
		// Method:    �����˷�������
		//************************************
		virtual void SendPwd();

		//************************************
		// Method:    ���͵�¼����������
		//************************************
		virtual void SendLoginSrvRequestPck();

		//************************************
		// Method:    ��¼����ɹ��¼�����
		//************************************
		virtual void OnLoginSrvSuccess();

		//************************************
		// Method:    ����������
		//************************************
		virtual void SendKeepAlive(int clientId = 0) override;

		//************************************
		// Method:    ��ʧ�������¼�����
		// Parameter: count:	������ʧ����
		// Parameter: b:	�Ƿ��ѳ�������������
		//************************************
		virtual void OnMissKeepAlive(int count, bool b = true) override;

	public:
		//************************************
		// Method:    ����
		// Parameter: Packet & pck
		//************************************
		virtual void SendPck(Packet& pck);
	};
}