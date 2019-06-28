#pragma once
#include "Include/Lib1/Def1.h"
#include "tc/TcpClient.h"
#include "tc/Timer.h"

using namespace tc;

namespace lib1
{
	// ����˿ͻ�����
	class PacketServerClient
	{
	public:
		PacketServerClient(int clientId, void* pSrv, bool bNeedVertify = true);
		virtual ~PacketServerClient();

	protected:
		int nClientId;		// client id
		void* pSrv;			// LibServer
		bool bNeedVertify;	// �Ƿ���Ҫ�ͻ��˷�������
		bool bVertified;	// �Ƿ�����֤�ͻ�������
		int nMissCount;		// ������ʧ�������Ĵ���
		Timer	t1;			// ���붨ʱ��
		Timer	t2;			// ���͵�¼�����������ʱ��
		Timer	t3;			// ��������ʱ��

	public:
		//************************************
		// Method:    ��ȡ�ͻ���id
		//************************************
		int GetClientId();
		
		//************************************
		// Method:    ��ȡ�Ƿ���֤��ͨ��
		//************************************
		bool IsVertified();

		//************************************
		// Method:    �����ͻ����¼�����
		//************************************
		void OnCreate();

		//************************************
		// Method:    �ͻ��˹ر��¼�����
		//************************************
		void OnClose();

		//************************************
		// Method:    ��֤�����¼�����
		// Return:	  �Ƿ��������
		// Parameter: pBuf:		������
		// Parameter: len:		����������
		//************************************
		void OnVertifyPwd(BYTE* pBuf, int len);

		//************************************
		// Method:    ��¼����������¼��������
		// Parameter: data:	������
		//************************************
		void OnLoginSrvRequest(PacketData& data);

		//************************************
		// Method:    �������¼��������
		// Parameter: data:	������
		//************************************
		void OnKeepAlive(PacketData& data);

		//************************************
		// Method:    ��ʧ�������¼��������
		//************************************
		void OnMissKeepAlive();

		void OnTimer(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);
	};


	class TimerCallback_PacketServerClient
	{
	public:
		static void OnTimer(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);
	};
}