#pragma once

#include <tchar.h>
#include <vector>
#include "MemoryTool.h"
#include "ProtocolMgr.h"
#include "SocketClientPlus.h"

namespace TCPCommunication
{
	template<typename TPackageType, typename TPackageBase, typename TProtocolMgr>
	//��1��ģ�����:	�����Ͷ���
	//��2��ģ�����:	�������Ͷ���
	//��3��ģ�����:	CProtocolMgr���ͻ���CProtocolMgr��������
	class CTCPClientMgr
	{
	private:
		//CTCPClientMgr�ض���
		typedef CTCPClientMgr<TPackageType, TPackageBase, TProtocolMgr>	CTCPClientMgrSelf;

	protected:
		//����ָ��:�յ�ҵ���
		typedef void(*LPOnRecvBusinessPackage)(TPackageType type, void* data);

	protected:
		CSocketClientPlus<CTCPClientMgrSelf> m_socket;//socket�ͻ��˹������
		TProtocolMgr m_protocol;//Э��������
		CByteStream* m_stream;//�ֽ�������
		CByteStream* m_streamCatch;//�ֽ����������
		LPOnRecvBusinessPackage m_lpfn;//ҵ�����ݺ���ָ��

	public:
		CTCPClientMgr()
		{
			m_streamCatch = NULL;
			m_lpfn = NULL;
			m_stream = NULL;
		};

		~CTCPClientMgr()
		{
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
			m_socket.Dispose();
		};

		//************************************
		// Method:    ��ʼ��
		// FullName:  TCPCommunication::CTCPClientMgr<TPackageType, TPackageBase, TProtocolMgr>::Init
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		// ip: �����IP
		// port: ����˶˿�
		// lpfn: �ͻ����հ��ص�����ָ��
		// recvBufLen: �հ���������С
		//************************************
		virtual bool Init(TCHAR* ip, int port, LPOnRecvBusinessPackage lpfn, int recvBufLen = 1024, int socketRecvBufLen = 1024)
		{
			if (m_stream == NULL)//ֻ��ʼ��һ��
			{
				m_stream = new CByteStream(recvBufLen);
				m_lpfn = lpfn;
				m_protocol.Init();
				m_socket.Init(ip, port, &CTCPClientMgrSelf::OnRecvData, this, socketRecvBufLen);
				return m_socket.StartConnect();
			}
			return true;
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
		virtual void OnRecvData(BYTE buf[], int len)
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
			int headlen = m_protocol.GetHeadLen();
			if (m_stream->GetDataLen() > headlen)
			{
				int len = 0;
				TPackageType type = m_protocol.GetPackageType(m_stream->GetBuf(), headlen);//��ȡ������
				if ((int)type != m_protocol.GetInvalidPackage())
				{
					int datalen = m_protocol.GetDataLen(m_stream->GetBuf(), headlen);//��ȡ�������ݳ���
					int packgetlen = datalen + headlen;//������ܳ���
					BYTE* buf = m_stream->Read(packgetlen);//���ֽ��������ж�ȡһ������������
					if (buf != NULL)
					{
						void* data = m_protocol.Unpacket(buf, packgetlen);//���
						delete buf;
						if (AnalyticsPackage(type, (TPackageBase*)data) && m_lpfn)
						{
							m_lpfn(type, data);
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
			if (type == m_protocol.GetKeepAlivePackage())//������
			{
				bool b = m_protocol.ValidateKeepAlivePackage(data);
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
			IPackageMgr* mgr = m_protocol.GetPackageMgr(type);
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
		virtual bool Send(TPackageType type, TPackageBase* data)
		{
			int len = 0;
			BYTE* buf = m_protocol.Packet(type, data, &len);
			return m_socket.SendData(buf, len);
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
			BYTE* buf = m_protocol.Packet(type, data, &len);
			m_socket.OnRecvData(buf, len);
			delete buf;
		};
	};
}