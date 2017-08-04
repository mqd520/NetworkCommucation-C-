#pragma once
#include "SocketMgr.h"
#include "PacketBase.h"
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	//tcp�Ự
	class CTcpConnection
	{
	private:
		CSocketMgr m_mgr;

	protected:
		SOCKET m_peerSocket;//�Զ�socket
		SOCKET m_localSocket;//����socket
		BYTE* m_pRecvBuf;
		int m_nRecvBufLen;

	private:
		SOCKET GetRecvSocket();

	public:
		CTcpConnection(SOCKET localSocket, SOCKET peerSocket);
		~CTcpConnection();

		SOCKET GetLocalSocket();

		SOCKET GetPeerSocket();

		//************************************
		// Method:    ��������(ͬ��)
		// Returns:   �Ƿ�ɹ�
		// Parameter: ������ָ��
		// Parameter: ����������
		//************************************
		bool SendData(BYTE buf[], int len);

		//************************************
		// Method:    ���͵��������(ͬ��)
		// Returns:   �Ƿ�ɹ�
		// Parameter: �����
		//************************************
		bool SendPacket(PacketBase* pack);

		//************************************
		// Method:    �������������(ͬ��)
		// Returns:   �Ƿ�ɹ�
		// Parameter: ���������
		//************************************
		bool BatchSendPacket(vector<PacketBase*> packs);

		//************************************
		// Method:    �����ݿɶ�
		//************************************
		void OnReadData();
	};
}