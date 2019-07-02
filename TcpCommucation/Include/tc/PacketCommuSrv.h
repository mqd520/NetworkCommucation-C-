#pragma once
#include "PacketHeadBase.h"
#include "MemoryStream.h"
#include "TcpEvt.h"

namespace tc
{
	// ���ڰ���ͨ�ŷ���
	class PacketCommuSrv
	{
	public:
		PacketCommuSrv(const int nHeadLen, PacketHeadBase header);

	protected:
		const int nHeadLen;			// ��ͷ����
		PacketHeadBase header;
		MemoryStream ms;			// �ڴ�������

	protected:
		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnRecvTcpEvent(TcpEvt* pEvt);

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

		//************************************
		// Method:    ����ԭʼ��������
		// Returns:   �Ƿ���ɹ�
		// Parameter: header:	��ͷ
		// Parameter: pBuf:		������
		// Parameter: len:		����������
		//************************************
		virtual bool ProcessOriginPckBuf(PacketHeadBase& header, BYTE* pBuf, int len);

		//************************************
		// Method:    Ԥ�������
		// Parameter: data:	������
		//************************************
		virtual void PreProcessPck(PacketData& data);

		//************************************
		// Method:    ������¼��������
		// Parameter: data:	������
		//************************************
		virtual void OnProcessPck(PacketData& data);
	};
}