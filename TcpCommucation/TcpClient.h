#pragma once
#include "SocketAPI.h"
#include "TcpService.h"

namespace tc
{
	//tcp�ͻ���
	class CTcpClient : public CTcpService
	{
	public:
		CTcpClient(TCHAR* strServerIP, int nServerPort);
		~CTcpClient();

	private:
		CSocketAPI m_socketAPI;//
		bool m_bIsConnecting;//�Ƿ����ڽ�������
		bool m_bIsConnected;//�Ƿ���������

	private:
		//************************************
		// Method:    ��ʼ��
		//************************************
		void Init();

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