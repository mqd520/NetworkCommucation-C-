#pragma once

#include <tchar.h>
#include <vector>
#include "MemoryTool.h"
#include "Interface.h"
#include "TcpClientT.h"

namespace NetworkCommunication
{
	template<typename TPackageType, typename TPackageBase>
	//Э�����
	//��1��ģ�����:	�����Ͷ���
	//��2��ģ�����:	�����������ඨ��
	class CProtocolMgr
	{
	private:
		//CProtocolMgr�ض���
		typedef CProtocolMgr<TPackageType, TPackageBase>	CProtocolMgrSelf;

	protected:
		//************************************
		// Method:    �ͻ����յ��������ݺ���ָ��
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::LPOnRecvBusinessData
		// Access:    protected 
		// Returns:   void
		// Qualifier: ������
		// Parameter: ����ṹ��ָ��
		//************************************
		typedef void(*LPOnRecvPackageBodyData)(TPackageType type, void* data);

		//��������Ϣ
		typedef struct tagPackageMgrInfo
		{
			TPackageType type;//������
			IPackageMgr* mgr;//��������
		}PackageMgrInfo, *LPPackageMgrInfo;

	protected:
		CTcpClientT<CProtocolMgr> m_tcp;//tcp�ͻ��˶���
		CByteStream* m_stream;//�ֽ�������
		CByteStream* m_streamCatch;//�ֽ����������
		LPOnRecvPackageBodyData m_lpfnRecvData;//�յ����ݺ���ָ��
		int m_nPackageHeadLen;//��ͷ����
		int m_nInvalidPackage;//��Ч��
		int m_nKeepAlive;//������
		vector<PackageMgrInfo> m_vecPackageMgr;//������������
		BYTE* m_pPackageHeadBuf;//��ͷ������ָ��
		bool m_bKeepAlive;//�Ƿ�ʹ��������

	public:
		CProtocolMgr() :
			m_lpfnRecvData(NULL),
			m_streamCatch(NULL),
			m_stream(NULL),
			m_nPackageHeadLen(0),
			m_nInvalidPackage(0),
			m_nKeepAlive(0),
			m_pPackageHeadBuf(NULL),
			m_bKeepAlive(false)
		{

		};

	protected:
		//************************************
		// Method:    ���������͵���������
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::AssoicatePackageType
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void AssoicatePackageType()
		{

		};

		//************************************
		// Method:    ��֤������
		// FullName:  ProtocolMgr::CProtocolMgr<TPackageType, TPackageBase>::ValidateKeepAlivePackage
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		// Parameter: ������
		//************************************
		virtual bool ValidateKeepAlivePackage(TPackageBase* data)
		{
			return true;
		}

		//************************************
		// Method:    ��ʼ����ͷ������
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::InitPackageHeadBuf
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: ������
		// Parameter: ����
		//************************************
		virtual void InitPackageHeadBuf(TPackageType type, int len)
		{

		};

		//************************************
		// Method:    ��֤���յ��İ�ͷ�������Ƿ���Ч(����������Ϊ��ͷ����)
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::ValidatePackageHead
		// Access:    virtual protected 
		// Returns:   bool
		// Qualifier:
		// Parameter: ������
		//************************************
		virtual bool ValidatePackageHead(BYTE buf[])
		{
			return false;
		};

		//************************************
		// Method:    ��֤�������Ƿ���Ч
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::ValidatePackageType
		// Access:    virtual protected 
		// Returns:   bool
		// Qualifier:
		// Parameter: ������
		//************************************
		virtual bool ValidatePackageType(TPackageType type)
		{
			return false;
		};

		//************************************
		// Method:    ���������¼�����
		// FullName:  CServer3Mgr::OnRecvData
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: BYTE buf[]
		// Parameter: int len
		//************************************
		virtual bool OnRecvData(BYTE buf[], int len)
		{
			if (m_streamCatch)
			{
				m_stream->Write(m_streamCatch);//�ӻ����ж�ȡ����д�뵽��ǰ������
				if (m_streamCatch->GetDataLen() == 0)//������������ʹ��
				{
					delete m_streamCatch;
					m_streamCatch = NULL;
				}
				else
				{
					if (len > 0)
					{
						m_streamCatch->Write(buf, len);//buf��Դ�ڷ����,��buf�洢�ڻ�������
					}
					Unpacket();
					OnRecvData(NULL, 0);//�����ӻ������ж�ȡ����
				}
			}
			if (len > 0)//buf��Դ�ڷ����
			{
				int len1 = m_stream->Write(buf, len);//ʵ��д��ĳ���
				Unpacket();
				if (len1 < len)
				{
					m_streamCatch = new CByteStream(len - len1);//������δ��ȫ���洢����,��Ҫ����������洢����
					m_streamCatch->Write(buf + len1, len - len1);
					OnRecvData(NULL, 0);//�����ӻ������ж�ȡ����
				}
			}
			else
			{
				Unpacket();
			}

			return false;
		};

	public:
		~CProtocolMgr()
		{
			for (vector<PackageMgrInfo>::iterator it = m_vecPackageMgr.begin(); it < m_vecPackageMgr.end(); ++it)
			{
				if (it->mgr)
				{
					delete it->mgr;
				}
			}
			if (m_stream)
			{
				delete m_stream;
				m_stream = NULL;
			}
			if (m_streamCatch)
			{
				delete m_streamCatch;
				m_streamCatch = NULL;
			}
			if (m_pPackageHeadBuf)
			{
				delete m_pPackageHeadBuf;
			}
		};

		virtual void Init(TCHAR* ip, int port, LPOnRecvPackageBodyData lpfnRecvData, LPOnRecvNotifyEvt lpfnNotifyEvt = NULL, int proBufLen = 1024,
			int tcpBufLen = 1024, bool autoReconnect = true, int reconnectTimes = 0, int reconnectTimeSpan = 1500, int connectTimeout = 2000)
		{
			if (m_stream == NULL)//ֻ��ʼ��һ��
			{
				m_pPackageHeadBuf = new BYTE[m_nPackageHeadLen];
				AssoicatePackageType();//���������ͺͰ�������
				m_stream = new CByteStream(proBufLen);//�������ջ������ֽ�������
				m_lpfnRecvData = lpfnRecvData;
				m_tcp.Init(ip, port, lpfnNotifyEvt, tcpBufLen, autoReconnect, reconnectTimes, reconnectTimeSpan, connectTimeout);
				m_tcp.SetCallbackT(&CProtocolMgrSelf::OnRecvData, this);//���ó�Ա�����ص�
				return m_tcp.Connect();
			}
		};

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
		virtual BYTE* PacketFromBuf(TPackageType type, BYTE buf[], int bufLen, int* packetLen)
		{
			*packetLen = m_nPackageHeadLen + bufLen;
			BYTE* data = new BYTE[*packetLen];
			memcpy(data, m_pPackageHeadBuf, m_nPackageHeadLen);//������ͷ����
			memcpy(data + m_nPackageHeadLen, buf, bufLen);//������������
			return data;
		};

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
		virtual BYTE* Packet(TPackageType type, TPackageBase* data, int* packetLen)
		{
			IPackageMgr* mgr = GetPackageMgr(type);
			if (mgr)
			{
				int len = 0;
				BYTE* buf = mgr->Unparse((void*)data, &len);
				if (len > 0)
				{
					BYTE* result = PacketFromBuf(type, buf, len, packetLen);
					delete buf;
					return result;
				}
			}
			return NULL;
		};

		//************************************
		// Method:    �ӻ�������(������ͷ�Ͱ���)������һ������ṹ������
		// FullName:  Protocol3::CProtocol3Handle::Unpacket
		// Access:    public 
		// Returns:   ����ṹ��ָ��
		// Qualifier:
		// Parameter: ������������ָ��
		// Parameter: ����������
		//************************************
		virtual TPackageBase* Unpacket(BYTE buf[], int len)
		{
			TPackageBase* p = NULL;
			if (len > m_nPackageHeadLen)
			{
				TPackageType type = GetPackageType(buf, len);
				IPackageMgr* mgr = GetPackageMgr(type);
				if (mgr)
				{
					p = (TPackageBase*)mgr->Parse(buf + m_nPackageHeadLen, len - m_nPackageHeadLen);
				}
			}
			return p;
		};

		//************************************
		// Method:    ��ȡ��ͷ����
		// FullName:  Protocol3::CProtocol3Handle::GetHeadLen
		// Access:    public 
		// Returns:   ��ͷ����
		// Qualifier:
		//************************************
		virtual int GetHeadLen()
		{
			return m_nPackageHeadLen;
		};

		//************************************
		// Method:    �ӻ������л�ȡ�������ݳ���
		// FullName:  Protocol3::CProtocol3Handle::GetDataLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: ������ָ��
		// Parameter: ����������
		//************************************
		virtual int GetDataLen(BYTE buf[], int len)
		{
			return m_nPackageHeadLen;
		};

		//************************************
		// Method:    �ӻ������л�ȡ������
		// FullName:  Protocol3::CProtocol3Handle::GetPackageType
		// Access:    public 
		// Returns:   ������
		// Qualifier:
		// Parameter: ������ָ��
		// Parameter: ����������
		//************************************
		virtual TPackageType GetPackageType(BYTE buf[], int len)
		{
			return TPackageType(m_nInvalidPackage);
		};

		//************************************
		// Method:    ��ȡ��������(���÷������ͷ�ָ��)
		// FullName:  Protocol3::CProtocol3Handle::GetMgr
		// Access:    protected static 
		// Returns:   Protocol3::Package3Mgr*
		// Qualifier:
		// Parameter: ������
		//************************************
		virtual IPackageMgr* GetPackageMgr(TPackageType type)
		{
			IPackageMgr* mgr = NULL;
			for (vector<PackageMgrInfo>::iterator it = m_vecPackageMgr.begin(); it < m_vecPackageMgr.end(); ++it)
			{
				if (it->type == type)
				{
					mgr = it->mgr;
					break;
				}
			}
			return mgr;
		};

		//************************************
		// Method:    ��ȡ���建����ָ��
		// FullName:  Protocol3::CProtocol3Handle::GetDataBuf
		// Access:    public static 
		// Returns:   ���建����ָ��
		// Qualifier:
		// Parameter: ��������ָ�� 
		// Parameter: ������������
		//************************************
		virtual BYTE* GetDataBuf(BYTE* buf, int len)
		{
			int datalen = GetDataLen(buf, len);
			int headlen = GetHeadLen();
			BYTE* result = new BYTE[datalen];
			memcpy(result, buf + headlen, datalen);
			return result;
		};

		//************************************
		// Method:    ��ȡ��ͷ������
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::GetPackageHeadBuf
		// Access:    virtual public 
		// Returns:   ��ͷ������
		// Qualifier:
		//************************************
		virtual BYTE* GetPackageHeadBuf()
		{
			BYTE* buf = new BYTE[m_nPackageHeadLen];
			memcpy(buf, m_pPackageHeadBuf, m_nPackageHeadLen);
			return buf;
		};

		//************************************
		// Method:    ���
		// FullName:  CServer3Mgr::Unpacket
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Unpacket()
		{
			if (m_stream->GetDataLen() > m_nPackageHeadLen)//���ݳ��ȱ�����ڰ��峤��(ָʾ�����ݵ���)
			{
				if (!ValidatePackageHead(m_stream->GetBuf()))//��֤��ͷ�Ƿ���Ч
				{
					m_stream->Detele(m_nPackageHeadLen);//ɾ����Ч��ͷ����
					return;
				}
				TPackageType type = GetPackageType(m_stream->GetBuf(), m_nPackageHeadLen);//��ȡ������
				if (!ValidatePackageType(type))
				{

				}
				if ((int)type != m_nInvalidPackage)//��֤�Ƿ���Ч��
				{
					int datalen = GetDataLen(m_stream->GetBuf(), m_nPackageHeadLen);//��ȡ�������ݳ���
					int packgetlen = datalen + m_nPackageHeadLen;//������ܳ���
					BYTE* buf = m_stream->Read(packgetlen);//���ֽ��������ж�ȡһ������������
					if (buf != NULL)
					{
						void* data = Unpacket(buf, packgetlen);//���
						delete buf;
						if (AnalyticsPackage(type, (TPackageBase*)data) && m_lpfnRecvData)//������
						{
							m_lpfnRecvData(type, data);
						}
						else
						{
							ReleasePackage(type, (TPackageBase*)data);
						}
					}
				}
			}
		};

		//************************************
		// Method:    ������,��ʾ�Ƿ���Ҫ��������
		// FullName:  CServer3Mgr::AnalyticsPackage
		// Access:    public 
		// Returns:   ����Ҫ��������
		// Qualifier:
		// Parameter: ������
		// Parameter: ����ṹ��ָ��
		//************************************
		virtual bool AnalyticsPackage(TPackageType type, TPackageBase* data)
		{
			if (type == m_nKeepAlive&&m_bKeepAlive)//������
			{
				bool b = ValidateKeepAlivePackage(data);
				if (!b)
				{
					//����
				}
				return true;
			}
			return true;
		};

		//************************************
		// Method:    �ͷŰ���ṹ��
		// FullName:  CServer3Mgr::ReleasePackage
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: ������
		// Parameter: ����ṹ��ָ��
		//************************************
		virtual void ReleasePackage(TPackageType type, TPackageBase* data)
		{
			IPackageMgr* mgr = GetPackageMgr(type);
			if (mgr)
			{
				mgr->Release((void*)data);
			}
		};

		//************************************
		// Method:    ����
		// FullName:  CServer3Mgr::Send
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: ������
		// Parameter: ����ṹ��ָ��
		//************************************
		virtual bool SendData(TPackageType type, TPackageBase* data)
		{
			int len = 0;
			BYTE* buf = Packet(type, data, &len);
			return m_tcp.SendData(buf, len);
		};

		//************************************
		// Method:    �ر�����
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::CloseConnect
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CloseConnect()
		{
			m_tcp.CloseConnect();
		};

		//************************************
		// Method:    ���ӷ����
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::Reconnect
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Connect()
		{
			if (!m_tcp.GetConnectStatus())
			{
				m_tcp.Connect();
			}
		};

		//************************************
		// Method:    ��ȡtcp�ͻ��˶���
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::GetTcpObj
		// Access:    virtual public 
		// Returns:   NetworkCommunication::CTcpClientT*
		// Qualifier:
		//************************************
		virtual CTcpClient GetTcpClientObj()
		{
			return m_tcp;
		};

		//************************************
		// Method:    ģ��һ�η���˷���
		// FullName:  CServer3Mgr::SimulateServer3Data
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: ������
		// Parameter: ����ṹ��ָ��
		//************************************
		virtual void SimulateServerData(TPackageType type, TPackageBase* data)
		{
			int len = 0;
			BYTE* buf = Packet(type, data, &len);
			m_tcp.SimulateServerData(buf, len);
			delete buf;
		};
	};
}