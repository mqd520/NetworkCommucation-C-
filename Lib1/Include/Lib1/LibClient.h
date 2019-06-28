#pragma once
#include "tc/TcpClient.h"
#include "../../LibSrv1.h"
#include "tc/Timer.h"

using namespace tc;

namespace lib1
{
	// ���ڰ���ͨ�ŷ���ͻ���
	class LibClient : public TcpClient, public LibSrv1
	{
	public:
		//************************************
		// Method:    ���캯��
		// Parameter: type:	��������
		// Parameter: bNeedVertify:	���ӳɹ����Ƿ���Ҫ��������
		// Parameter: string ip
		// Parameter: int port
		//************************************
		LibClient(EServiceType type = EServiceType::None, bool bNeedVertify = true, string ip = "", int port = 0);
		virtual ~LibClient();

	protected:
		bool bNeedVertify;		// �Ƿ���Ҫ��������
		Timer t1;				// ��ʧ������ʱ����
		Timer t2;				// ����������ʱ����

	private:
		friend class TimerCallback_PacketClient;

		//************************************
		// Method:    ��������
		//************************************
		void SendPwd();

		//************************************
		// Method:    ���͵�¼����������
		//************************************
		void SendLoginSrvRequest();

		//************************************
		// Method:    ����������
		//************************************
		void SendKeepAlive();

		void OnTimerKeepAlive(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);

	protected:
		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnRecvTcpEvent(TcpEvt* pEvt) override;

		//************************************
		// Method:    ���ӷ��������¼�����
		//************************************
		virtual void OnConnectCpl(TcpEvt* pEvt) override;

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
		// Method:    ��¼����˽�����¼��������
		// Parameter: data:	������
		//************************************
		virtual void OnLoginSrvResult(PacketData& data) override;

		//************************************
		// Method:    �������¼��������
		// Parameter: data:	������
		//************************************
		virtual void OnKeepAlive(PacketData& data) override;

	public:
		//************************************
		// Method:    ����
		// Parameter: PacketBase & pck
		//************************************
		virtual void SendPck(PacketBase& pck);

		//************************************
		// Method:    �˳�
		//************************************
		virtual void Exit() override;
	};

	class TimerCallback_PacketClient
	{
	public:
		static void OnTimer(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);
	};
}