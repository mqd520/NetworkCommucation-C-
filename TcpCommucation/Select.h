#pragma once
#include <vector>
#include "Def.h"
#include "Include/tc/SocketTool.h"
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// select��
	class CSelect
	{
	public:
		CSelect();
		~CSelect();

	private:
		vector<SelectSocketData> vecListenSocket;	//��Ҫ������socket����
		fd_set fsRead;			// �ɶ�socket����
		fd_set fsWrite;			// ��дsocket����
		fd_set fsExcept;		// �쳣socket����
		vector<vector<SelectSocketData>> groupSocket;	// socket����
		timeval m_selectTimeout;
		vector<ProcessingSocketData> vecProcessingSocketData; // ���ڽ��д����socket���ݼ���
		CThreadLock m_lock1;	// �߳���, ���vecListenSocket����
		CThreadLock m_lock2;	// �߳���, ���vecProcessingSocketData����

	private:
		//************************************
		// Method:    ����ȴ�������socket
		//************************************
		void ProcessSocket();

		//************************************
		// Method:    ������socket���з���
		//************************************
		void CalcSocketGroup();

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
		// Method:    ���ָ��socket�Ƿ��쳣
		// Parameter: ����socket��������
		//************************************
		void CheckSocketExcept(SelectSocketData socketData);

		//************************************
		// Method:    ���ָ��socket�Ƿ�ɶ�
		// Parameter: ����socket��������
		//************************************
		void CheckSocketCanRead(SelectSocketData socketData);

		//************************************
		// Method:    ���ָ��socket�Ƿ��д
		// Parameter: ����socket��������
		//************************************
		void CheckSocketCanWrite(SelectSocketData socketData);

	public:
		//************************************
		// Method:    socket�����Ƿ�Ϊ��
		//************************************
		bool IsEmpty();

		//************************************
		// Method:    ���socket
		// Parameter: socket
		// Parameter: socket����: ESocketType
		//************************************
		void AddSocket(SOCKET socket, ESocketType type);

		//************************************
		// Method:    �Ƴ�ָ����socket
		// Parameter: socket
		// Parameter: �Ƿ�ر�,Ĭ�Ϲر�
		//************************************
		void RemoveSocket(SOCKET socket, bool close = true);

		//************************************
		// Method:    ��ѯsocket�ź�
		//************************************
		void Select();

		//************************************
		// Method:    socket�źŴ�������¼�����
		// Parameter: socket
		// Parameter: socket����: ESocketSingalType
		//************************************
		void OnProcessingSocketCmp(SOCKET socket, ESocketSingalType type);

		//************************************
		// Method:    ָʾ�û��˳�
		//************************************
		void Exit();
	};
}