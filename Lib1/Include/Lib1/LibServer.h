#pragma once
#include "tc/TcpServer.h"
#include "../../LibSrv1.h"
#include "../../PacketServerClientMgr.h"

namespace lib1
{
	// ���ڰ���ͨ�ŷ����������
	class LibServer : public TcpServer, public LibSrv1
	{
	public:
		//************************************
		// Method:    ���캯��
		// Parameter: type:	��������
		// Parameter: bNeedVertify:	���ӳɹ����Ƿ���Ҫ��������
		// Parameter: string ip
		// Parameter: int port
		//************************************
		LibServer(EServiceType type = EServiceType::None, bool bNeedVertify = true, string ip = "", int port = 0);
		virtual ~LibServer();

	protected:
		int nClientId;						// client id
		PacketServerClientMgr clientMgr;	// client mgr
		bool bNeedVertify;					// �Ƿ���Ҫ��֤�ͻ�������

	protected:
		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnRecvTcpEvent(TcpEvt* pEvt) override;

		//************************************
		// Method:    �յ��������¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnRecvConnection(TcpEvt* pEvt) override;

		//************************************
		// Method:    ���ӶϿ��¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnConnDiconnect(TcpEvt* pEvt) override;

		//************************************
		// Method:    �յ��Զ������¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnRecvPeerData(TcpEvt* pEvt) override;

		//************************************
		// Method:    ��¼�����������¼��������
		// Parameter: data:	������
		//************************************
		virtual void OnLoginSrvRequest(PacketData& data) override;

		//************************************
		// Method:    �������¼��������
		// Parameter: data:	������
		//************************************
		virtual void OnKeepAlive(PacketData& data) override;

	public:
		//************************************
		// Method:    ����
		//************************************
		virtual void SendPck(PacketBase& pck, int clientId);

		//************************************
		// Method:    �رտͻ���
		//************************************
		virtual void CloseClient(int clientId, bool b = true) override;

		//************************************
		// Method:    �˳�
		//************************************
		virtual void Exit() override;

		//************************************
		// Method:    ��ʧ�������¼��������
		// Parameter: clientId:	client id
		// Parameter: count: ������ʧ����
		//************************************
		virtual void OnMissKeepAlive(int clientId, int count);
	};
}