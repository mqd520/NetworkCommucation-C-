#pragma once

#include <tchar.h>
#include <vector>
#include "MemoryTool.h"
#include "Def.h"
#include "TcpClientT.h"

namespace NetworkCommunication
{
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
		typedef void(*LPOnRecvPackageBodyData)(int type, LPPackageBase data);

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

	private:
		BYTE* m_pKeepAliveBuf;//������������
		int m_nKeepAliveBufLen;//����������������

	protected:
		CTcpClientT<CProtocolMgr> m_tcp;//tcp�ͻ��˶���
		CByteStream* m_stream;//�ֽ�������
		LPOnRecvPackageBodyData m_lpfnRecvData;//�յ����ݺ���ָ��
		int m_nPackageHeadLen;//��ͷ����
		int m_nKeepAlive;//����������
		vector<PackageMgrInfo> m_vecPackageMgr;//������������
		HANDLE m_hMutexStream;//�ֽ����������
		ThreadInfo m_tiTimer;//�������߳���Ϣ
		UINT m_nKeepAliveTimeout;//������ʱ��
		bool m_bRecvKeepAlive;//�Ƿ����յ�������
		int m_nKeepAliveFailCount;//������ʧ�ܼ���,0�������յ��Է�������
		int m_nKeepAliveFailMaxCount;//������ʧ�ܼ������ֵ,����ֵ����Ϊ�Է��ѵ���
		LPPackageBase m_pKeepAlive;//������ָ��


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
		// Parameter: int proBufLen
		// Parameter: int tcpBufLen
		// Parameter: bool autoReconnect
		// Parameter: int reconnectTimes
		// Parameter: int reconnectTimeSpan
		// Parameter: int connectTimeout
		//************************************
		virtual void Init(TCHAR* ip, int port, LPOnRecvPackageBodyData lpfnRecvData, LPOnRecvNotifyEvt lpfnNotifyEvt = NULL, int proBufLen = 1024,
			int tcpBufLen = 1024, bool autoReconnect = true, int reconnectTimes = 0, int reconnectTimeSpan = 1500, int connectTimeout = 2000);

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