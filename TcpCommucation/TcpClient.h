#pragma once
#include "Include/tc/SocketTool.h"
#include "TcpService.h"

namespace tc
{
	// tcp�ͻ�����
	class TcpClient : public TcpService
	{
	public:
		TcpClient(string ip = "", int port = 0);
		virtual ~TcpClient();

	private:
		bool bIsConnecting;		// �Ƿ����ڽ�������
		bool bIsConnected;		// �Ƿ���������
		bool bIsReconnect;		// �Ƿ���Ҫ�Զ���������

	private:
		//************************************
		// Method:    ��ʼ��
		//************************************
		void Init();

		//************************************
		// Method:    ����������Ϣ
		// Parameter: ip:	�����IP
		// Parameter: port:	����˶˿�
		//************************************
		void SetConnectInfo(string ip, int port);

		//************************************
		// Method:    ���ӷ����
		//************************************
		void ConnectServer();

	protected:
		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		void OnRecvTcpEvent(TcpEvt* pEvent);

	public:
		//************************************
		// Method:    ���ӷ����
		//************************************
		void Connect();

		//************************************
		// Method:    �ر�����
		// Parameter: b:	�Ƿ�������ӹر��¼�
		//************************************
		void Close(bool b = true);

		//************************************
		// Method:    ��Զ˷�������
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		//************************************
		void Send(BYTE* pBuf, int len);
	};
}