#pragma once

#include <tchar.h>
#include "ByteStream.h"
#include "PacketBase.h"
#include "PacketHeadBase.h"
#include "OtherTool.h"
#include "TcpClientT.h"

namespace NetworkCommunication
{
	//Э��ͻ��˹���
	class CProtocolClientMgr
	{
	public:
		//Э������¼�����
		enum ProtocolEvtType
		{
			fatal,//���ش���
			tcpfailed,//tcp����ʧ��
			tcpsuccess,//tcp���ӳɹ�
			NetError,//�������
			serverdis,//����˶Ͽ�����
			Info,//��Ϣ
			LoginServerSuccess,//Э���¼�ɹ�
			LoginServerFailed,//Э���¼ʧ��
			LoseServer//ʧȥ�����(���������ʧ��)
		};

	protected:
		//************************************
		// Method:    ���հ��庯��ָ��
		// Qualifier: ������
		// Parameter: ���建����ָ��
		// Parameter: ���建��������
		//************************************
		typedef void(*LPOnRecvPack)(int cmd, BYTE* buf, int len);

		//************************************
		// Method:    �յ�Э���¼�����
		// Qualifier: �¼�����
		// Parameter: ��Ϣ
		//************************************
		typedef void(*LPOnRecvProtocolEvt)(ProtocolEvtType type, TCHAR* msg);

		//�߳���Ϣ
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//�߳̾��
			DWORD dwThreadID;//�߳�ID
		}ThreadInfo, *LPThreadInfo;

	protected:
		CTcpClientT<CProtocolClientMgr> m_tcp;//tcp�ͻ��˶���
		CByteStream* m_stream;//�ֽ�������
		LPOnRecvPack m_lpfnRecvData;//�յ��������ݺ���ָ��
		int m_nPackageHeadLen;//��ͷ����
		int m_nKeepAlive;//����������
		HANDLE m_hMutexStream;//�ֽ����������
		int m_nKeepAliveTimespan;//���������ʱ��
		bool m_bRecvKeepAlive;//�Ƿ����յ�������
		int m_nKeepAliveFailCount;//������ʧ�ܼ���,0�������յ��Է�������
		int m_nKeepAliveFailMaxCount;//������ʧ�ܼ������ֵ,����ֵ����Ϊ�Է��ѵ���
		int m_nReconnectServerMaxCount;//ʧȥ���������(��tcp����,��ⲻ��ָ��������������),�Զ����������ֵ(0:������)
		int m_nReconnectServerCount;//ʧȥ��������Ӻ�,�����ӷ���˵Ĵ���
		PacketBase* m_pKeepAlive;//������ָ��
		PacketHeadBase* m_pHead;//��ͷָ��
		LPOnRecvProtocolEvt m_lpfnRecvProtocolEvt;//�յ�Э���¼�����ָ��
		int m_nStreamBufLen;//������������
		int m_nTcpBufLen;//tcp���ջ���������
		bool m_bAutoReconnect;//�Ƿ��Զ�����
		int m_nReconnectTimes;//������������
		int m_nReconnectTimeSpan;//�������ʱ��
		int m_nConnectTimeout;//���ӳ�ʱʱ��
		TcpDataRecvType m_sendType;//tcp���ݷ��ͷ�ʽ
		CTimerT<CProtocolClientMgr>* m_timer;//��������ʱ��
		TCHAR m_strServerIP[20];//�����IP
		int m_nServerPort;//����˶˿�

	protected:
		//************************************
		// Method:    ��ͷ��Ч�¼�����
		//************************************
		virtual void OnPackageHeadInvalid();

		//************************************
		// Method:    ���������¼�����
		// Returns:   �Ƿ����ͷŻ�����
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual bool OnRecvData(BYTE buf[], int len);

		//************************************
		// Method:    ֪ͨ�������а������ݵ���
		// Parameter: ������
		// Parameter: ���建����
		// Parameter: ���建��������
		//************************************
		virtual void NotifyRecver(int cmd, BYTE* buf, int len);

		//************************************
		// Method:    ��ʼ���(ѭ�������н��,ֱ�����г��Ȳ����ͷ����)
		//************************************
		virtual void StartUnpacket();

		//************************************
		// Method:    Ԥ�����
		// Returns:   �Ƿ���Ҫ�����ߴ���
		// Parameter: ������
		// Parameter: ��������
		// Parameter: ������������
		//************************************
		virtual bool PreprocessPack(int cmd, BYTE* buf, int len);

		//************************************
		// Method:    ���
		// Returns:   ��������
		// Parameter: ����ָ��
		// Parameter: ������������
		//************************************
		BYTE* Pack(PacketBase* data, int * len);

		//************************************
		// Method:    ����tcp�¼�����
		// Returns:   �Ƿ��Ѵ���
		// Parameter: �¼�����
		// Parameter: ��Ϣ
		//************************************
		void OnRecvTcpEvt(TcpEvtType type, TCHAR* msg);

		//************************************
		// Method:    tcp���ӳɹ��¼�����
		// Parameter: ��Ϣ
		//************************************
		virtual void OnTcpConnectSuccess(TCHAR* msg);

		//************************************
		// Method:    tcp����ʧ���¼�����
		// Parameter: ��Ϣ
		//************************************
		virtual void OnTcpConnectFail(TCHAR* msg);

		//************************************
		// Method:    ����˶Ͽ������¼�����
		// Parameter: ��Ϣ
		//************************************
		virtual void OnServerDisconnect(TCHAR* msg);

		//************************************
		// Method:    ʧȥ������¼�����
		// Parameter: ��Ϣ
		//************************************
		virtual void OnLoseServer();

		//************************************
		// Method:    ����Э���¼�
		// Parameter: �¼�����
		// Parameter: ��Ϣ
		//************************************
		void SendProtocolEvt(ProtocolEvtType type, TCHAR* msg);

		//************************************
		// Method:    ����ǰ�¼�����
		// Parameter: ������
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual void OnBeforeSendPack(int cmd, BYTE* buf, int len);

		//************************************
		// Method:    ���յ�һ���������¼�����
		// Returns:   ���Ƿ���Ч
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual bool OnRecvCmpPacket(BYTE* buf, int len);

		//************************************
		// Method:    �Ƿ�ָ����������
		// Returns:   �Ƿ�ָ����������
		//************************************
		bool IsAssignedKeepAlive();

		//************************************
		// Method:    ��ʼ����������
		//************************************
		void StartKeepAlive();

		//************************************
		// Method:    ��������ʱ�¼�����
		//************************************
		bool OnKeepAliveTimeout();

		//************************************
		// Method:    ��������
		//************************************
		void Reconnect();

		//����������
		virtual void SendKeepAlivePack();

	public:
		CProtocolClientMgr();
		~CProtocolClientMgr();

		//************************************
		// Method:    ��ʼ��
		// Parameter: �����IP
		// Parameter: ����˶˿�
		// Parameter: ���հ�����ָ��
		// Parameter: ����Э���¼�����ָ��
		//************************************
		virtual void Init(TCHAR* ip, int port, LPOnRecvPack lpfnRecvData, LPOnRecvProtocolEvt lpfnRecvProtocolEvt = NULL);

		//************************************
		// Method:    ���ӷ����
		//************************************
		void Connect();

		//************************************
		// Method:    ����
		// Returns:   �Ƿ�ɹ�
		// Parameter: ����ָ��
		//************************************
		bool SendPack(PacketBase* data);

		//************************************
		// Method:    ���ͻ�����
		// Returns:   �Ƿ��ͳɹ�
		// Parameter: ������
		// Parameter: ����������
		//************************************
		bool SendData(BYTE* buf, int len);

		//************************************
		// Method:    �ر�����
		//************************************
		void CloseConnect();

		//************************************
		// Method:    ��ȡtcp�ͻ��˶���
		//************************************
		CTcpClient GetTcpClientObj();

		//************************************
		// Method:    ģ��һ�η���˷���
		// Parameter: ����ṹ��ָ��
		//************************************
		void SimulateServerData(PacketBase* data);
	};
}