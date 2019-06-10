#pragma once

#include <WinSock2.h>
#include <vector>
#include "Def.h"
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// socket���ݹ�����
	class SocketDataMgr
	{
	public:
		SocketDataMgr();
		~SocketDataMgr();

	private:
		vector<SelectSocketData> vecSocketData;	// socket���ݼ���
		CThreadLock lock1;	// �߳���, ���: vecSocketData

	public:
		//************************************
		// Method:    ���һ��socket
		// Parameter: SOCKET socket:	socket
		// Parameter: ESocketType type:	socket����
		//************************************
		void Add(SOCKET socket, ESocketType type);

		//************************************
		// Method:    �Ƴ�һ��socket
		// Parameter: SOCKET socket:	socket
		//************************************
		void Remove(SOCKET socket);

		//************************************
		// Method:    �������socket
		//************************************
		void Clear();

		//************************************
		// Method:    ��ȡָ�����͵�socket���ݼ���
		// Parameter: ESocketType type:	socket����
		//************************************
		vector<SOCKET> GetSocket(ESocketType type);

		//************************************
		// Method:    ��ȡ����socket����
		//************************************
		vector<SelectSocketData> GetSocket();

		//************************************
		// Method:    ��ȡָ��socket������
		// Parameter: SOCKET socket:	socket
		//************************************
		ESocketType GetSocketType(SOCKET socket);
	};
}