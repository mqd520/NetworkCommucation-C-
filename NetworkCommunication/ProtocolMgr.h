#pragma once

#include <tchar.h>
#include <vector>
#include "MemoryTool.h"
#include "Def.h"
#include "TcpClientT.h"

namespace NetworkCommunication
{
	//Э������¼�����
	enum ProtocolEvtType
	{
		tcpError = TcpEvtType::error,//������tcp����
		keepAliveFail = 2,//������ʧ��
		online = 10,//�����������
		offline = 11//�����������
	};

	//Э�����
	class CProtocolMgr
	{
	protected:
		//************************************
		// Method:    �ͻ����յ��������ݺ���ָ��
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::LPOnRecvBusinessData
		// Access:    protected 
		// Returns:   void
		// Qualifier: ������
		// Parameter: ����ṹ��ָ��
		//************************************
		typedef void(*LPOnRecvPackageData)(int type, LPPackageBase data);

		//************************************
		// Method:    �յ�Э���¼�����
		// FullName:  NetworkCommunication::CProtocolMgr::LPOnRecvProtocolEvt
		// Access:    protected 
		// Returns:   �Ƿ��Ѵ����¼�
		// Qualifier: �¼�����
		// Parameter: ��Ϣ
		//************************************
		typedef bool(*LPOnRecvProtocolEvt)(ProtocolEvtType type, TCHAR* msg);

		//��������Ϣ
		typedef struct tagPackageMgrInfo
		{
			int type;//������
			IPackageMgr* mgr;//��������
		}PackageMgrInfo, *LPPackageMgrInfo;

		//�߳���Ϣ
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//�߳̾��
			DWORD dwThreadID;//�߳�ID
		}ThreadInfo, *LPThreadInfo;

	protected:
		CTcpClientT<CProtocolMgr> m_tcp;//tcp�ͻ��˶���
		CByteStream* m_stream;//�ֽ�������
		LPOnRecvPackageData m_lpfnRecvData;//�յ��������ݺ���ָ��
		int m_nPackageHeadLen;//��ͷ����
		int m_nKeepAlive;//����������
		vector<PackageMgrInfo> m_vecPackageMgr;//������������
		HANDLE m_hMutexStream;//�ֽ����������
		ThreadInfo m_tiTimer;//�������߳���Ϣ
		int m_nKeepAliveTimespan;//���������ʱ��
		bool m_bRecvKeepAlive;//�Ƿ����յ�������
		int m_nKeepAliveFailCount;//������ʧ�ܼ���,0�������յ��Է�������
		int m_nKeepAliveFailMaxCount;//������ʧ�ܼ������ֵ,����ֵ����Ϊ�Է��ѵ���
		int m_nReconnectServerMaxCount;//ʧȥ���������(��tcp����,��ⲻ��ָ��������������),�Զ����������ֵ(0:������)
		int m_nReconnectServerCount;//ʧȥ��������Ӻ�,�����ӷ���˵Ĵ���
		bool m_bIsOnlineCallEvt;//�Ƿ��Ѵ��������¼�
		bool m_bIsOfflineCallEvt;//�Ƿ��Ѵ��������¼�
		LPPackageBase m_pKeepAlive;//������ָ��
		BYTE* m_pKeepAliveBuf;//������������
		int m_nKeepAliveBufLen;//����������������
		LPOnRecvProtocolEvt m_lpfnRecvProtocolEvt;//�յ�Э���¼�����ָ��
		int m_nStreamBufLen;//������������
		int m_nTcpBufLen;//tcp���ջ���������
		bool m_bAutoReconnect;//�Ƿ��Զ�����
		int m_nReconnectTimes;//������������
		int m_nReconnectTimeSpan;//�������ʱ��
		int m_nConnectTimeout;//���ӳ�ʱʱ��

	private:
		//************************************
		// Method:    ��ʼ��������
		// FullName:  NetworkCommunication::CProtocolMgr::InitKeepAlive
		// Access:    private 
		// Returns:   void
		// Qualifier:
		//************************************
		void InitKeepAlive();

	protected:
		//************************************
		// Method:    ���������͵���������
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::AssoicatePackageType
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void AssociatePackageType();

		//************************************
		// Method:    ��֤������
		// FullName:  ProtocolMgr::CProtocolMgr<TPackageType, TPackageBase>::ValidateKeepAlivePackage
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		// Parameter: ������
		//************************************
		virtual bool ValidateKeepAlivePackage(LPPackageBase data);

		//************************************
		// Method:    ��֤���յ��İ�ͷ�������Ƿ���Ч(����������Ϊ��ͷ����)
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::ValidatePackageHead
		// Access:    virtual protected 
		// Returns:   bool
		// Qualifier:
		// Parameter: ������
		//************************************
		virtual bool ValidatePackageHead(BYTE buf[]);

		//************************************
		// Method:    ��֤�������Ƿ���Ч
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::ValidatePackageType
		// Access:    virtual protected 
		// Returns:   bool
		// Qualifier:
		// Parameter: ������
		//************************************
		virtual bool ValidatePackageType(int type);

		//************************************
		// Method:    ���������¼�����
		// FullName:  CServer3Mgr::OnRecvData
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual bool OnRecvData(BYTE buf[], int len);

		//************************************
		// Method:    ��ʼ���(ѭ�������н��,ֱ�����г��Ȳ����ͷ����)
		// FullName:  CServer3Mgr::Unpacket
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void StartUnpacket();

		//************************************
		// Method:    ������,��ʾ�Ƿ��ɵ����ߴ����
		// FullName:  CServer3Mgr::AnalyticsPackage
		// Access:    public 
		// Returns:   �Ƿ��ɵ����ߴ���
		// Qualifier:
		// Parameter: ������
		// Parameter: ����ṹ��ָ��
		//************************************
		virtual bool AnalyticsPackage(int type, LPPackageBase data);

		//************************************
		// Method:    �����߳�
		// FullName:  NetworkCommunication::CProtocolMgr::CleanThread
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		void CleanThread();

		//************************************
		// Method:    �յ�tcp�¼�����
		// FullName:  NetworkCommunication::CProtocolMgr::OnRecvTcpEvt
		// Access:    protected 
		// Returns:   bool
		// Qualifier:
		// Parameter: TcpClientEvtType type
		// Parameter: TCHAR * msg
		//************************************
		bool OnRecvTcpEvt(TcpEvtType type, TCHAR* msg);

		//************************************
		// Method:    tcp���ӳɹ��¼�����
		// FullName:  NetworkCommunication::CProtocolMgr::OnTcpConnectSuccess
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnTcpConnectSuccess();

		//************************************
		// Method:    tcp����ʧ���¼�����
		// FullName:  NetworkCommunication::CProtocolMgr::OnTcpConnectFail
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnTcpConnectFail();

		//************************************
		// Method:    ���ӷ���˳ɹ��¼�����
		// FullName:  NetworkCommunication::CProtocolMgr::OnConnectServerSuccsss
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnConnectServerSuccsss();

		//************************************
		// Method:    ���ӷ����ʧ���¼�����
		// FullName:  NetworkCommunication::CProtocolMgr::OnConnectServerFail
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnConnectServerFail();

		//************************************
		// Method:    ����Э���¼�
		// FullName:  NetworkCommunication::CProtocolMgr::SendProtocolEvt
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		// Parameter: �¼�����
		// Parameter: ��Ϣ
		//************************************
		void SendProtocolEvt(ProtocolEvtType type, TCHAR* msg);

		//************************************
		// Method:    ���ͻ�����׼������¼�����
		// FullName:  NetworkCommunication::CProtocolMgr::OnSendBufReadyCmp
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual void OnSendBufReadyCmp(BYTE* buf, int len);

		//************************************
		// Method:    ���ջ�����(������)׼������¼�����
		// FullName:  NetworkCommunication::CProtocolMgr::OnRecvBufReadyCmp
		// Access:    virtual protected 
		// Returns:   �������Ƿ���Ч
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual bool OnRecvBufReadyCmp(BYTE* buf, int len);

		//************************************
		// Method:    ��ʼ������
		// FullName:  NetworkCommunication::CProtocolMgr::StartKeepAlive
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		void StartKeepAlive();

		//************************************
		// Method:    �Ƿ�ָ����������
		// FullName:  NetworkCommunication::CProtocolMgr::IsAssignedKeepAlive
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		bool IsAssignedKeepAlive();

	public:
		CProtocolMgr();
		~CProtocolMgr();

		//************************************
		// Method:    ��ʼ��
		// FullName:  NetworkCommunication::CProtocolMgr::Init
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: TCHAR * ip
		// Parameter: int port
		// Parameter: LPOnRecvPackageBodyData lpfnRecvData
		// Parameter: LPOnRecvNotifyEvt lpfnNotifyEvt
		//************************************
		virtual void Init(TCHAR* ip, int port, LPOnRecvPackageData lpfnRecvData, LPOnRecvProtocolEvt lpfnRecvProtocolEvt = NULL);

		//************************************
		// Method:    ���(���÷��ͷŻ�����ָ��)
		// FullName:  Protocol3::CProtocol3Handle::Packet
		// Access:    public 
		// Returns:   ��������ָ��
		// Qualifier:
		// Parameter: ������
		// Parameter: �������ݻ�����ָ��
		// Parameter: �������ݻ���������
		// Parameter: ������������(���)
		//************************************
		virtual BYTE* PacketFromBuf(int type, BYTE buf[], int bufLen, int* packetLen);

		//************************************
		// Method:    ��ȡ��ͷ������
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::GetPackageHeadBuf
		// Access:    virtual protected 
		// Returns:   ������
		// Qualifier:
		// Parameter: ������
		// Parameter: �������ݳ���
		//************************************
		virtual BYTE* GetPackageHeadBuf(int type, int len);

		//************************************
		// Method:    ���(���÷��ͷŻ�����ָ��)
		// FullName:  Protocol3::CProtocol3Handle::Packet
		// Access:    public static 
		// Returns:   ��������ָ��
		// Qualifier:
		// Parameter: ������
		// Parameter: ����ṹ��ָ��
		// Parameter: ������������(���)
		//************************************
		virtual BYTE* Packet(int type, LPPackageBase data, int* packetLen);

		//************************************
		// Method:    �ӻ�������(������ͷ�Ͱ���)������һ������ṹ������
		// FullName:  Protocol3::CProtocol3Handle::Unpacket
		// Access:    public 
		// Returns:   ����ṹ��ָ��
		// Qualifier:
		// Parameter: ������������ָ��
		// Parameter: ����������
		//************************************
		virtual LPPackageBase Unpacket(BYTE buf[], int len);

		//************************************
		// Method:    ��ȡ��ͷ����
		// FullName:  Protocol3::CProtocol3Handle::GetHeadLen
		// Access:    public 
		// Returns:   ��ͷ����
		// Qualifier:
		//************************************
		virtual int GetHeadLen();

		//************************************
		// Method:    �ӻ������л�ȡ�������ݳ���
		// FullName:  Protocol3::CProtocol3Handle::GetDataLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: ������ָ��
		// Parameter: ����������
		//************************************
		virtual int GetDataLen(BYTE buf[], int len);

		//************************************
		// Method:    �ӻ������л�ȡ������
		// FullName:  Protocol3::CProtocol3Handle::GetPackageType
		// Access:    public 
		// Returns:   ������
		// Qualifier:
		// Parameter: ������ָ��
		// Parameter: ����������
		//************************************
		virtual int GetPackageType(BYTE buf[], int len);

		//************************************
		// Method:    ��ȡ��������(���÷������ͷ�ָ��)
		// FullName:  Protocol3::CProtocol3Handle::GetMgr
		// Access:    protected static 
		// Returns:   Protocol3::Package3Mgr*
		// Qualifier:
		// Parameter: ������
		//************************************
		virtual IPackageMgr* GetPackageMgr(int type);

		//************************************
		// Method:    ��ȡ���建����ָ��
		// FullName:  Protocol3::CProtocol3Handle::GetDataBuf
		// Access:    public static 
		// Returns:   ���建����ָ��
		// Qualifier:
		// Parameter: ��������ָ�� 
		// Parameter: ������������
		//************************************
		virtual BYTE* GetDataBuf(BYTE* buf, int len);

		//************************************
		// Method:    �ͷŰ���ṹ��
		// FullName:  CServer3Mgr::ReleasePackage
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: ������
		// Parameter: ����ṹ��ָ��
		//************************************
		virtual void ReleasePackage(int type, LPPackageBase data);

		//************************************
		// Method:    ����
		// FullName:  CServer3Mgr::Send
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: ������
		// Parameter: ����ṹ��ָ��
		//************************************
		virtual bool SendData(int type, LPPackageBase data);

		//************************************
		// Method:    �ر�����
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::CloseConnect
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CloseConnect();

		//************************************
		// Method:    ���ӷ����
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::Reconnect
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Connect();

		//************************************
		// Method:    ��ȡtcp�ͻ��˶���
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::GetTcpObj
		// Access:    virtual public 
		// Returns:   NetworkCommunication::CTcpClientT*
		// Qualifier:
		//************************************
		virtual CTcpClient GetTcpClientObj();

		//************************************
		// Method:    ģ��һ�η���˷���
		// FullName:  CServer3Mgr::SimulateServer3Data
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: ������
		// Parameter: ����ṹ��ָ��
		//************************************
		virtual void SimulateServerData(int type, LPPackageBase data);

		//************************************
		// Method:    ��������ʱ���¼�����(��CProtocolMgr�������������,�ͻ����������)
		// FullName:  NetworkCommunication::CProtocolMgr::OnTimerKeepAlive
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnTimerKeepAlive();

		//************************************
		// Method:    �Է��Ƿ�����
		// FullName:  NetworkCommunication::CProtocolMgr::IsOnline
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		bool IsOnline();
	};
}