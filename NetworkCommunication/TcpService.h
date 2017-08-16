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
		// Method:    ���յ��µĿͻ��������¼�����
		// Parameter: �����socket	
		// Parameter: �Զ�socket����
		//************************************
		virtual void OnRecvNewConnection(ServerSocketData server, PeerSocketData client);

		//************************************
		// Method:    �Զ������ر��¼�����
		// Parameter: �����socket	
		// Parameter: �Զ�socket����
		//************************************
		virtual void OnPeerCloseSocket(PeerSocketData data);

		//************************************
		// Method:    ���յ��Զ�socket�����¼�����(���÷��ͷŻ�����ָ��)
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		// Parameter: �Զ�socket����
		// Return:	  �Ƿ��Ѵ������
		//************************************
		virtual bool OnRecvPeerData(BYTE buf[], int len, PeerSocketData data);
	};
}