#pragma once
#include "SocketAPI.h"
#include "Def.h"
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	//对端socket数据管理
	class CPeerSocketDataMgr
	{
	private:
		vector<PeerSocketData> m_vec;//对端数据集合

	public:
		CPeerSocketDataMgr();
		~CPeerSocketDataMgr();

		//增加一个对端Socket数据
		void PushPeerSocketData(PeerSocketData data);

		static PeerSocketData Create(SOCKET peer, SOCKET local);

		//************************************
		// Method:    获取指定对端socket的相关数据
		// Parameter: 对端socket	
		//************************************
		PeerSocketData GetDataByPeer(SOCKET peer);

		//************************************
		// Method:    获取指定本地socket的相关数据
		// Parameter: 本地socket	
		//************************************
		PeerSocketData GetDataByLocal(SOCKET local);
	};
}