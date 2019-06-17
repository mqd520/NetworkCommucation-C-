#pragma once
#include <vector>
#include "Def.h"
#include "Include/tc/SocketTool.h"
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
		// Method:    ����socket�쳣
		// Parameter: socket��������
		// Parameter: fs
		//************************************
		void processSocketExcept(SocketInfoData socketData, fd_set& fs);

		//************************************
		// Method:    ����socket�ɶ�
		// Parameter: socket��������
		// Parameter: fs
		//************************************
		void processSocketRead(SocketInfoData socketData, fd_set& fs);

	public:
		//************************************
		// Method:    ��ѯsocket�ź�
		//************************************
		void QuerySingal(vector<SocketInfoData>& vec);
	};
}