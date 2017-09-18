#pragma once
#include <vector>
#include "SocketAPI.h"
#include "Thread.h"
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	//select��
	class CSelect : public CThreadEntry
	{
	private:
		CSocketAPI m_socketAPI;//socket api
		vector<SelectSocketData> m_vecSocket;//��Ҫ������socket����
		CThread* m_thread;//�̶߳���
		fd_set m_readFdSet;
		fd_set m_exceptFdSet;
		vector<vector<SelectSocketData>> m_group;//socket����
		timeval m_selectTimeout;//
		int m_nBufLen;//���ջ������ֽ���󳤶�

	private:
		//************************************
		// Method:    ����ȴ�������socket
		//************************************
		void ProcessSocket();

		// ������socket���з���
		void CalcSocketGroup();

		//************************************
		// Method:    ���ָ��socket�Ƿ�ɶ�
		// Parameter: ����socket��������
		//************************************
		void CheckSocketCanRead(SelectSocketData socketData);

		//************************************
		// Method:    ���ָ��socket�Ƿ��쳣
		// Parameter: ����socket��������
		//************************************
		void CheckSocketExcept(SelectSocketData socketData);

		//************************************
		// Method:    ����������
		// Parameter: �����server
		//************************************
		void RecvNewConnection(SOCKET server);

		//************************************
		// Method:    ���նԶ�����
		// Parameter: �������ݵ�socket
		//************************************
		void RecvPeerData(SOCKET recv);

	public:
		CSelect();
		~CSelect();

		//************************************
		// Method:    �����߳�
		//************************************
		void Run();

		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadRun();

		//************************************
		// Method:    ���socket
		// Parameter: socket
		// Parameter: ����
		//************************************
		void AddSocket(SOCKET socket, int type);

		// �Ƴ�ָ��socket
		void RemoveSocket(SOCKET socket);
	};
}