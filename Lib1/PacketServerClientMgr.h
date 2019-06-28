#pragma once
#include "PacketServerClient.h"

namespace lib1
{
	// 
	class PacketServerClientMgr
	{
	public:
		PacketServerClientMgr();
		~PacketServerClientMgr();

	protected:
		vector<PacketServerClient*> vecClients;		// �ͻ��˶��󼯺�

	public:
		//************************************
		// Method:    ����һ���ͻ��˶���
		// Parameter: int clientId
		//************************************
		PacketServerClient* CreateClient(int clientId, void* pSrv, bool bNeedVertify = true);

		//************************************
		// Method:    ��ȡ�ͻ��˶���
		// Parameter: int clientId
		//************************************
		PacketServerClient* GetClient(int clientId);

		//************************************
		// Method:    �Ƴ�һ���ͻ��˶���
		// Parameter: int clientId
		//************************************
		void Remove(int clientId);

		//************************************
		// Method:    �ر�����
		//************************************
		void CloseAll();
	};
}