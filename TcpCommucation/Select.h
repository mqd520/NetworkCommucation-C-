#pragma once
#include <vector>
#include "Def.h"
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// select��
	class Select
	{
	public:
		Select();
		~Select();

	private:
		vector<vector<SocketInfoData>> vecGroupSocket;		// socket����
		CThreadLock lock2;									// �߳���, ���vecProcessingSocketData����

	private:
		//************************************
		// Method:    ������socket���з���
		//************************************
		void CalcSocketGroup(vector<SocketInfoData>& vec);

		//************************************
		// Method:    socket�����쳣
		// Parameter: socket��������
		// Parameter: fs
		//************************************
		void OnSocketExcept(SocketInfoData& socketData, fd_set& fs);

		//************************************
		// Method:    ����socket�ɶ�
		// Parameter: socket��������
		// Parameter: fs
		//************************************
		void OnSocketRead(SocketInfoData& socketData, fd_set& fs);

		void OnRecvNewConn(SocketInfoData& socketData);

		void OnRecvData(SocketInfoData& socketData);

	public:
		//************************************
		// Method:    ��ѯsocket�ź�
		//************************************
		void QuerySingal(vector<SocketInfoData>& vec);
	};
}