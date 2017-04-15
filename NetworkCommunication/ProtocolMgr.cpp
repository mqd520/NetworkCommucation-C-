#include "stdafx.h"
#include "ProtocolMgr.h"

#define PackageTypeNullVal	(-999)//�����Ϳ�ֵ,��ʾû������

namespace NetworkCommunication
{
	//��ʼ�������߳�
	DWORD WINAPI StartTimer(LPVOID lpParam);

	CProtocolMgr::CProtocolMgr() :
		m_lpfnRecvData(NULL),
		m_stream(NULL),
		m_nPackageHeadLen(0),
		m_nKeepAlive(PackageTypeNullVal),
		m_tiTimer({ 0 }),
		m_nKeepAliveTimeout(1 * 1000),
		m_bRecvKeepAlive(false),
		m_nKeepAliveFailCount(0),
		m_nKeepAliveFailMaxCount(3)
	{
		m_hMutexStream = ::CreateMutex(NULL, false, NULL);
	};

	CProtocolMgr::~CProtocolMgr()
	{
		CleanThread();
		if (m_hMutexStream)
		{
			::CloseHandle(m_hMutexStream);
		}
		if (m_stream)
		{
			delete m_stream;
			m_stream = NULL;
		}
		for (vector<PackageMgrInfo>::iterator it = m_vecPackageMgr.begin(); it < m_vecPackageMgr.end(); ++it)
		{
			if (it->mgr)
			{
				delete it->mgr;
			}
		}
	}

	void CProtocolMgr::AssociatePackageType()
	{

	};

	bool CProtocolMgr::ValidateKeepAlivePackage(LPPackageBase data)
	{
		return true;
	}

	bool CProtocolMgr::ValidatePackageHead(BYTE buf[])
	{
		return false;
	}

	bool CProtocolMgr::ValidatePackageType(int type)
	{
		return false;
	}

	bool CProtocolMgr::OnRecvData(BYTE buf[], int len)
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
	}

	void CProtocolMgr::StartUnpacket()
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
			int type = GetPackageType(m_stream->GetBuf(), m_nPackageHeadLen);//��ȡ������
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
				if (AnalyticsPackage(type, (LPPackageBase)data))//�������Ƿ��ɵ����ߴ���
				{
					if (m_lpfnRecvData)
					{
						m_lpfnRecvData(type, (LPPackageBase)data);
					}
					else
					{
						ReleasePackage(type, (LPPackageBase)data);//�ͷŰ�����
					}
				}
				else
				{
					ReleasePackage(type, (LPPackageBase)data);//�ͷŰ�����
				}
			}
		}
	}

	bool CProtocolMgr::AnalyticsPackage(int type, LPPackageBase data)
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
	}

	void CProtocolMgr::Init(TCHAR* ip, int port, LPOnRecvPackageBodyData lpfnRecvData, LPOnRecvNotifyEvt lpfnNotifyEvt, int proBufLen,
		int tcpBufLen, bool autoReconnect, int reconnectTimes, int reconnectTimeSpan, int connectTimeout)
	{
		if (m_stream == NULL)//ֻ��ʼ��һ��
		{
			m_stream = new CByteStream(proBufLen);//�������ջ������ֽ�������
			m_lpfnRecvData = lpfnRecvData;
			AssociatePackageType();//���������ͺͰ�������
			if (m_nKeepAlive != PackageTypeNullVal)//ָ��������
			{
				m_tiTimer.hThread = ::CreateThread(NULL, 0, StartTimer, this, NULL, &(m_tiTimer.dwThreadID));
			}
			m_tcp.Init(ip, port, lpfnNotifyEvt, tcpBufLen, autoReconnect, reconnectTimes, reconnectTimeSpan, connectTimeout);
			m_tcp.SetCallbackT(&CProtocolMgr::OnRecvData, this);//���ó�Ա�����ص�
			return m_tcp.Connect();
		}
	}

	BYTE* CProtocolMgr::PacketFromBuf(int type, BYTE buf[], int bufLen, int* packetLen)
	{
		*packetLen = m_nPackageHeadLen + bufLen;
		BYTE* data = new BYTE[*packetLen];
		BYTE* bufHead = GetPackageHeadBuf(type, bufLen);
		memcpy(data, bufHead, m_nPackageHeadLen);//������ͷ����
		delete bufHead;
		memcpy(data + m_nPackageHeadLen, buf, bufLen);//������������
		return data;
	}

	BYTE* CProtocolMgr::GetPackageHeadBuf(int type, int len)
	{
		return NULL;
	}

	BYTE* CProtocolMgr::Packet(int type, LPPackageBase data, int* packetLen)
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
	}

	LPPackageBase CProtocolMgr::Unpacket(BYTE buf[], int len)
	{
		LPPackageBase p = NULL;
		if (len > m_nPackageHeadLen)
		{
			int type = GetPackageType(buf, len);
			IPackageMgr* mgr = GetPackageMgr(type);
			if (mgr)
			{
				p = (LPPackageBase)mgr->Parse(buf + m_nPackageHeadLen, len - m_nPackageHeadLen);
			}
		}
		return p;
	}

	int CProtocolMgr::GetHeadLen()
	{
		return m_nPackageHeadLen;
	}

	int CProtocolMgr::GetDataLen(BYTE buf[], int len)
	{
		return m_nPackageHeadLen;
	}

	int CProtocolMgr::GetPackageType(BYTE buf[], int len)
	{
		return -999;
	}

	IPackageMgr* CProtocolMgr::GetPackageMgr(int type)
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
	}

	BYTE* CProtocolMgr::GetDataBuf(BYTE* buf, int len)
	{
		int datalen = GetDataLen(buf, len);
		int headlen = GetHeadLen();
		BYTE* result = new BYTE[datalen];
		memcpy(result, buf + headlen, datalen);
		return result;
	}

	void CProtocolMgr::ReleasePackage(int type, LPPackageBase data)
	{
		IPackageMgr* mgr = GetPackageMgr(type);
		if (mgr)
		{
			mgr->Release((void*)data);
		}
	}

	bool CProtocolMgr::SendData(int type, LPPackageBase data)
	{
		int len = 0;
		BYTE* buf = Packet(type, data, &len);
		bool b = m_tcp.SendData(buf, len);
		delete buf;
		return b;
	}

	void CProtocolMgr::CloseConnect()
	{
		m_tcp.CloseConnect();
	}

	void CProtocolMgr::Connect()
	{
		if (!m_tcp.GetConnectStatus())
		{
			m_tcp.Connect();
		}
	}

	CTcpClient CProtocolMgr::GetTcpClientObj()
	{
		return m_tcp;
	}

	void CProtocolMgr::SimulateServerData(int type, LPPackageBase data)
	{
		int len = 0;
		BYTE* buf = Packet(type, data, &len);
		m_tcp.SimulateServerData(buf, len);
		delete buf;
	}

	void CProtocolMgr::CleanThread()
	{
		if (m_tiTimer.hThread)
		{
			::TerminateThread(m_tiTimer.hThread, 0);
			::CloseHandle(m_tiTimer.hThread);
			m_tiTimer = { 0 };
		}
	}

	void CProtocolMgr::OnTimerKeepAlive()
	{
		while (true)
		{
			if (m_nKeepAliveFailCount > 0)//û���յ�������
			{
				if (m_nKeepAliveFailCount > m_nKeepAliveFailMaxCount)//��������ʧ�����ֵ
				{
					//��Ϊ�Է��ѵ���
				}
				else
				{
					m_nKeepAliveFailCount++;
				}
			}

			//SendData(m_nKeepAlive,)

			::Sleep(m_nKeepAliveTimeout);
		}
	}

	LPPackageBase CProtocolMgr::GetKeepAlivePackage()
	{
		return NULL;
	}

	DWORD WINAPI StartTimer(LPVOID lpParam)
	{
		CProtocolMgr* mgr = (CProtocolMgr*)lpParam;
		mgr->OnTimerKeepAlive();
		return 0;
	}
}