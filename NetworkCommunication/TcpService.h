#pragma once
#include "Thread.h"
#include "Def.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	///tcp����
	class CTcpService
	{
	private:
		int m_nSrvType;

	private:
		void OnRecvNewConnection();

	public:
		~CTcpService();
		CTcpService(int srvType);

		// ��ȡtcp��������
		int GetSrvType();

		//************************************
		// Method:    ��ȡ�����socket����
		//************************************
		virtual ServerSocketData GetServerSocketData();

		//************************************
		// Method:    ���յ��µĿͻ�������
		// Parameter: �����socket	
		// Parameter: �Զ�socket����
		//************************************
		virtual void OnRecvNewConnection(ServerSocketData server, PeerSocketData client);

		virtual void OnPeerCloseSocket(PeerSocketData data);
	};
}