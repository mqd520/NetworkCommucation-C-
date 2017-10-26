#pragma once
#include <vector>
#include "SocketAPI.h"
#include "Def.h"
#include "ThreadLock.h"

using namespace std;

namespace NetworkCommunication
{
	//select��
	class CSelect
	{
	private:
		CSocketAPI m_socketAPI;//socket api
		vector<SelectSocketData> m_vecSocket;//��Ҫ������socket����
		fd_set m_readFdSet;//�ɶ�socket����
		fd_set m_writeFdSet;//��дsocket����
		fd_set m_exceptFdSet;//�쳣socket����
		vector<vector<SelectSocketData>> m_group;//socket����
		timeval m_selectTimeout;//
		vector<ProcessingSocketData> m_vecProcessingData;//���ڽ��д����socket���ݼ���
		CThreadLock m_lock1;//�߳���,���m_vecSocket����
		CThreadLock m_lock2;//�߳���,���m_vecProcessingData����

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
		// Parameter: �ź�����
		//************************************
		bool IsProcessingSingal(SOCKET socket, int type);

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
		CSelect();
		~CSelect();

		//************************************
		// Method:    socket�����Ƿ�Ϊ��
		//************************************
		bool IsEmpty();

		//************************************
		// Method:    ���socket
		// Parameter: socket
		// Parameter: ����
		//************************************
		void AddSocket(SOCKET socket, int type);

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
		// Parameter: �ź�����
		//************************************
		void OnProcessingSocketCmp(SOCKET socket, int type);
	};
}