#pragma once
#include "Include/tc/TcpService.h"
#include "Include/tc/MemoryStream.h"

namespace tc
{
	// ���ڰ���ͨ�ŷ���
	class PacketCommuSrv : public TcpService
	{
	public:
		PacketCommuSrv(string ip = "", int port = 0);

	protected:
		MemoryStream ms;			// �ڴ�������

	protected:
		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnRecvTcpEvent(TcpEvt* pEvt) override;

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
		// Method:    ������ջ���������
		// Parameter: pBuf:		������
		// Parameter: len:		����������
		// Parameter: clientId:	�ͻ���id
		//************************************
		virtual void ProcessRecvBuf(BYTE* pBuf, int len, int clientId = 0);

		//************************************
		// Method:    ������������
		//************************************
		virtual void ParsePacketBuf(vector<PacketData>& vec);
	};
}