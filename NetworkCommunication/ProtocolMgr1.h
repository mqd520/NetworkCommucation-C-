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
	class CProtocolMgr1
	{
	private:
		//CProtocolMgr�ض���
		typedef CProtocolMgr1<TPackageType, TPackageBase>	CProtocolMgrSelf;

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
		LPOnRecvPackageBodyData m_lpfnRecvData;//�յ����ݺ���ָ��
		int m_nPackageHeadLen;//��ͷ����
		TPackageType m_nKeepAlive;//����������
		vector<PackageMgrInfo> m_vecPackageMgr;//������������
		HANDLE m_hMutexStream;//�ֽ����������

	public:
		CProtocolMgr() :
			m_lpfnRecvData(NULL),
			m_stream(NULL),
			m_nPackageHeadLen(0)
		{
			m_hMutexStream = ::CreateMutex(NULL, false, NULL);
		};

	protected:
		//************************************
		// Method:    ���������͵���������
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::AssoicatePackageType
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void AssociatePackageType()
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
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual bool OnRecvData(BYTE buf[], int len)
		{
			int index = 0;//��ȡ��������ʼ����
			while (true)
			{
				::WaitForSingleObject(m_hMutexStream, INFINITE);
				int actualLen = m_stream->Write(buf + index, len);//����������д�뵽������,����ʵ��д���ֽڳ���
				if (m_stream->IsFull())//���������������,���̽��н������
				{
					::ReleaseMutex(m_hMutexStream);
					StartUnpacket();
				}
				else
				{
					if (actualLen < len)//ʵ�ʶ�ȡ����С�ڻ���������,����ѭ����ȡ������
					{
						index += actualLen;
						::ReleaseMutex(m_hMutexStream);
						continue;
					}
					else//�����������Ѷ�ȡ���,����ѭ��,���н������
					{
						::ReleaseMutex(m_hMutexStream);
						break;
					}
				}
			}

			delete buf;
			StartUnpacket();
			return true;
		};

		//************************************
		// Method:    ��ʼ���(ѭ�������н��,ֱ�����г��Ȳ����ͷ����)
		// FullName:  CServer3Mgr::Unpacket
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void StartUnpacket()
		{
			while (true)
			{
				::WaitForSingleObject(m_hMutexStream, INFINITE);//��ס�������

				//���ݳ���С�ڵ��ڰ�ͷ����(��ʾ����û�а�������,�������κδ���,������������)
				if (m_stream->GetDataLen() <= m_nPackageHeadLen)
				{
					::ReleaseMutex(m_hMutexStream);//����
					break;
				}
				if (!ValidatePackageHead(m_stream->GetBuf()))//��֤��ͷ�Ƿ���Ч
				{
					m_stream->Detele(m_nPackageHeadLen);//ɾ����Ч��ͷ����
					::ReleaseMutex(m_hMutexStream);//����
					continue;//�����´�ѭ��
				}
				TPackageType type = GetPackageType(m_stream->GetBuf(), m_nPackageHeadLen);//��ȡ������
				if (!ValidatePackageType(type))
				{
					m_stream->Detele(m_nPackageHeadLen);//ɾ����Ч��ͷ����
					::ReleaseMutex(m_hMutexStream);//����
					continue;//�����´�ѭ��
				}
				int datalen = GetDataLen(m_stream->GetBuf(), m_nPackageHeadLen);//��ȡ�������ݳ���
				int packgetlen = datalen + m_nPackageHeadLen;//������ܳ���
				if (packgetlen > m_stream->GetBufLen())//���ܳ��ȳ������ֽڳ�����Ϊ��Ч��
				{
					m_stream->Detele(m_nPackageHeadLen);//ɾ����Ч��ͷ����
					::ReleaseMutex(m_hMutexStream);//����
					continue;//�����´�ѭ��
				}
				BYTE* buf = m_stream->Read(packgetlen);//���ֽ��������ж�ȡһ������������
				::ReleaseMutex(m_hMutexStream);//����
				if (buf != NULL)
				{
					void* data = Unpacket(buf, packgetlen);//���
					delete buf;
					if (AnalyticsPackage(type, (TPackageBase*)data))//�������Ƿ��ɵ����ߴ���
					{
						if (m_lpfnRecvData)
						{
							m_lpfnRecvData(type, data);
						}
						else
						{
							ReleasePackage(type, (TPackageBase*)data);//�ͷŰ�����
						}
					}
					else
					{
						ReleasePackage(type, (TPackageBase*)data);//�ͷŰ�����
					}
				}
			}
		};

		//************************************
		// Method:    ������,��ʾ�Ƿ��ɵ����ߴ����
		// FullName:  CServer3Mgr::AnalyticsPackage
		// Access:    public 
		// Returns:   �Ƿ��ɵ����ߴ���
		// Qualifier:
		// Parameter: ������
		// Parameter: ����ṹ��ָ��
		//************************************
		virtual bool AnalyticsPackage(TPackageType type, TPackageBase* data)
		{
			if (type == m_nKeepAlive)//������
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
			if (m_hMutexStream)
			{
				::CloseHandle(m_hMutexStream);
			}
			if (m_stream)
			{
				delete m_stream;
				m_stream = NULL;
			}
		};

		virtual void Init(TCHAR* ip, int port, LPOnRecvPackageBodyData lpfnRecvData, LPOnRecvNotifyEvt lpfnNotifyEvt = NULL, int proBufLen = 1024,
			int tcpBufLen = 1024, bool autoReconnect = true, int reconnectTimes = 0, int reconnectTimeSpan = 1500, int connectTimeout = 2000)
		{
			if (m_stream == NULL)//ֻ��ʼ��һ��
			{
				m_stream = new CByteStream(proBufLen);//�������ջ������ֽ�������
				m_lpfnRecvData = lpfnRecvData;
				AssociatePackageType();//���������ͺͰ�������
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
			BYTE* bufHead = GetPackageHeadBuf(type, bufLen);
			memcpy(data, bufHead, m_nPackageHeadLen);//������ͷ����
			delete bufHead;
			memcpy(data + m_nPackageHeadLen, buf, bufLen);//������������
			return data;
		};

		//************************************
		// Method:    ��ȡ��ͷ������
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::GetPackageHeadBuf
		// Access:    virtual protected 
		// Returns:   ������
		// Qualifier:
		// Parameter: ������
		// Parameter: �������ݳ���
		//************************************
		virtual BYTE* GetPackageHeadBuf(TPackageType type, int len)
		{
			return NULL;
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
			return TPackageType(-999);
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
			bool b = m_tcp.SendData(buf, len);
			delete buf;
			return b;
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