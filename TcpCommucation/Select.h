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
		vector<vector<SelectSocketData>> vecGroupSocket;	// socket����
		vector<ProcessingSocketData> vecProcessingSocketData; // ���ڽ��д����socket���ݼ���
		CThreadLock lock2;	// �߳���, ���vecProcessingSocketData����

	private:
		//************************************
		// Method:    ����ȴ�������socket
		//************************************
		void ProcessSocket();

		//************************************
		// Method:    ������socket���з���
		//************************************
		void CalcSocketGroup(vector<SelectSocketData>& vec);

		//************************************
		// Method:    �ж�ָ��socket���ź��Ƿ����ڱ�����
		// Parameter: socket
		// Parameter: socket����: ESocketSingalType
		//************************************
		bool IsProcessingSingal(SOCKET socket, ESocketSingalType type);

		//************************************
		// Method:    �Ƴ����ڽ��д����socket
		// Parameter: socket
		//************************************
		void RemoveProcessingSocket(SOCKET socket);

		//************************************
		// Method:    ����socket�쳣
		// Parameter: socket��������
		// Parameter: fs
		//************************************
		void processSocketExcept(SelectSocketData socketData, fd_set& fs);

		//************************************
		// Method:    ����socket�ɶ�
		// Parameter: socket��������
		// Parameter: fs
		//************************************
		void processSocketRead(SelectSocketData socketData, fd_set& fs);

	public:
		//************************************
		// Method:    ��ѯsocket�ź�
		//************************************
		void QuerySingal(vector<SelectSocketData>& vec);

		//************************************
		// Method:    ָʾ�û��˳�
		//************************************
		void Exit();
	};
}