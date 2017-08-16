#pragma once
#include <vector>
#include "SocketAPI.h"
#include "Thread.h"
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	class CSelect
	{
	private:
		CSocketAPI m_socketAPI;
		vector<SelectSocketData> m_vecSocket;//��Ҫ������socket����
		bool m_bExit;//ָʾ�߳��Ƿ�Ӧ�ý���
		CThread* m_threadSelect;
		bool m_bSleep;//select�߳��Ƿ���sleep
		fd_set m_readSet;
		vector<vector<SelectSocketData>> m_group;
		timeval m_selectTimeout;

	private:
		//************************************
		// Method:    ��ʼ��ѯsocket״̬
		//************************************
		void StartSelect();

		// ������socket���з���
		void CalcSocketGroup();

		//���ָ��socket�ź�
		void CheckSocketSingal(SelectSocketData socket);

	public:
		CSelect();
		~CSelect();

		//************************************
		// Method:    ���socket
		// Parameter: socket
		// Parameter: ����
		//************************************
		void AddSocket(SOCKET socket, int type); 

		// �Ƴ�ָ��socket
		void RemoveSocket(SOCKET socket);

		//************************************
		// Method:    ����select�߳�
		//************************************
		void Run();

		//************************************
		// Method:    select�߳���ڵ�
		//************************************
		void ThreadEntry();
	};
}