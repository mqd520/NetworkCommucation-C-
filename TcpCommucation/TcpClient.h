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
		// Method:    ����
		//************************************
		void Reconnect();

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
		// Method:    ��Զ˷�������
		// Returns:   �Ƿ�ɹ�
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		// Parameter: �Ƿ��첽,Ĭ���첽����
		// Parameter: ʵ�ʷ����ֽڳ���
		//************************************
		bool Send(BYTE* pBuf, int len, bool asyncs = true, int* actualLen = NULL);
	};
}