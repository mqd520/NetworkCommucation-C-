#pragma once
#include "Def.h"
#include "Include/Lib1/Def1.h"

#include "tc/Def1.h"
#include "tc/PacketBase.h"
#include "tc/TcpClient.h"
#include "tc/TcpServer.h"
#include "tc/TcpEvt.h"
#include "tc/MemoryStream.h"

using namespace tc;

namespace lib1
{
	class LibSrv1
	{
	public:
		//************************************
		// Method:    ���캯��
		// Parameter: type:	��������
		//************************************
		LibSrv1(EServiceType type = EServiceType::None, void* pObj = NULL, ELibSrvType type1 = ELibSrvType::Client);
		virtual ~LibSrv1();

	private:
		void* pObj;					// 
		ELibSrvType libSrvType;		// ����������

	protected:
		EServiceType srvType;		// ��������
		MemoryStream ms;			// �ڴ�������

	private:
		string GetIp1();
		int GetPort1();

	protected:
		//************************************
		// Method:    ��־�¼�����
		// Parameter: type:	tcp��־����
		// Parameter: log:	��־����
		//************************************
		virtual void OnLog(ETcpLogType type, string log);

		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		void OnRecvTcpEvent(TcpEvt* pEvt);

		//************************************
		// Method:    ������ջ���������
		// Parameter: pBuf:		������
		// Parameter: len:		����������
		// Parameter: clientId:	�ͻ���id
		//************************************
		void ProcessRecvBuf(BYTE* pBuf, int len, int clientId = 0);

		//************************************
		// Method:    ������������
		//************************************
		vector<PacketData> ParsePacketBuf();

		//************************************
		// Method:    ���ӷ��������¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnConnectCpl(TcpEvt* pEvt);

		//************************************
		// Method:    ���ӶϿ��¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnConnDiconnect(TcpEvt* pEvt);

		//************************************
		// Method:    �յ��������¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnRecvConnection(TcpEvt* pEvt);

		//************************************
		// Method:    �յ��Զ������¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnRecvPeerData(TcpEvt* pEvt);

		//************************************
		// Method:    ������¼��������
		// Parameter: data:	������
		//************************************
		virtual void OnProcessPck(PacketData& data);

		//************************************
		// Method:    ����ҵ����¼��������
		// Parameter: data:	������
		//************************************
		virtual void OnProcessBusinessPck(PacketData& data);

		//************************************
		// Method:    �������¼��������
		// Parameter: data:	������
		//************************************
		virtual void OnKeepAlive(PacketData& data);

		//************************************
		// Method:    ��¼�����������¼��������
		// Parameter: data:	������
		//************************************
		virtual void OnLoginSrvRequest(PacketData& data);

		//************************************
		// Method:    ��¼����˽�����¼��������
		// Parameter: data:	������
		//************************************
		virtual void OnLoginSrvResult(PacketData& data);

		//************************************
		// Method:    ����
		//************************************
		virtual void SendPck1(PacketBase& pck, int clientId = 0);

	public:
		//************************************
		// Method:    ��ȡ��������
		//************************************
		virtual EServiceType GetSrvType();

		//************************************
		// Method:    ��־�¼�����
		// Parameter: type:	tcp��־����
		// Parameter: log:	��־����
		//************************************
		virtual void WriteLog(ETcpLogType type, string format, ...);
	};
}