#pragma once
#include "SocketAPI.h"
#include "Def.h"
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	//�Զ�socket���ݹ���
	class CPeerSocketDataMgr
	{
	private:
		vector<PeerSocketData> m_vec;//�Զ����ݼ���

	public:
		CPeerSocketDataMgr();
		~CPeerSocketDataMgr();

		//����һ���Զ�Socket����
		void PushPeerSocketData(PeerSocketData data);

		static PeerSocketData Create(SOCKET peer, SOCKET local);

		//************************************
		// Method:    ��ȡָ���Զ�socket���������
		// Parameter: �Զ�socket	
		//************************************
		PeerSocketData GetDataByPeer(SOCKET peer);

		//************************************
		// Method:    ��ȡָ������socket���������
		// Parameter: ����socket	
		//************************************
		PeerSocketData GetDataByLocal(SOCKET local);
	};
}