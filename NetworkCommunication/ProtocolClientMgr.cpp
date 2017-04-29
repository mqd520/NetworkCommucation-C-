#include "stdafx.h"
#include "ProtocolClientMgr.h"

#define PackageTypeNullVal	(-999)//�����Ϳ�ֵ,��ʾû������

namespace NetworkCommunication
{
	CProtocolClientMgr::CProtocolClientMgr() :
		m_lpfnRecvData(NULL),
		m_stream(NULL),
		m_nPackageHeadLen(0),
		m_nKeepAlive(PackageTypeNullVal),
		m_nKeepAliveTimespan(2 * 1000),
		m_bRecvKeepAlive(false),
		m_nKeepAliveFailCount(0),
		m_nKeepAliveFailMaxCount(3),
		m_nReconnectServerCount(0),
		m_nReconnectServerMaxCount(3),
		m_pKeepAlive(NULL),
		m_pKeepAliveBuf(NULL),
		m_nKeepAliveBufLen(0),
		m_lpfnRecvProtocolEvt(NULL),
		m_nStreamBufLen(1024),
		m_nTcpBufLen(1024),
		m_bAutoReconnect(true),
		m_nReconnectTimes(0),
		m_nReconnectTimeSpan(2000),
		m_nConnectTimeout(2000),
		m_sendType(TcpDataRecvType::single),
		m_pHead(NULL),
		m_timer(NULL)
	{
		m_hMutexStream = ::CreateMutex(NULL, false, NULL);
	}

	CProtocolClientMgr::~CProtocolClientMgr()
	{
		if (m_hMutexStream)
		{
			::CloseHandle(m_hMutexStream);
		}
		if (m_pHead)
		{
			delete m_pHead;
		}
		if (m_stream)
		{
			delete m_stream;
			m_stream = NULL;
		}
		if (m_pKeepAliveBuf)
		{
			delete m_pKeepAliveBuf;
			m_pKeepAliveBuf = NULL;
		}
		if (m_timer)
		{
			m_timer->Stop();
			delete m_timer;
			m_timer = NULL;
		}
		if (m_pKeepAlive)
		{
			delete m_pKeepAlive;
		}
		if (m_pKeepAliveBuf)
		{
			delete m_pKeepAliveBuf;
		}
		for (vector<PackageMgrInfo>::iterator it = m_vecPackageMgr.begin(); it < m_vecPackageMgr.end(); ++it)
		{
			if (it->mgr)
			{
				delete it->mgr;
			}
		}
	}

	bool CProtocolClientMgr::ValidateKeepAlivePacket(PacketBase* data)
	{
		return true;
	}

	bool CProtocolClientMgr::OnRecvData(BYTE buf[], int len)
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

	void CProtocolClientMgr::StartUnpacket()
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
			m_pHead->Write(m_stream->GetBuf(), m_nPackageHeadLen);//д�뻺��������ͷ
			if (!m_pHead->IsValid())//��֤��ͷ�Ƿ���Ч
			{
				m_stream->Detele(m_nPackageHeadLen);//ɾ����Ч��ͷ����
				::ReleaseMutex(m_hMutexStream);//����
				OnPackageHeadInvalid();//��ͷ��Ч�¼�����
				continue;//�����´�ѭ��
			}
			int cmd = m_pHead->GetCmd();//��ȡ������
			int packetLen = m_pHead->GetPacketLen();//��ȡ�������ݳ���
			int packetTotalLen = packetLen + m_nPackageHeadLen;//��ȡ���ܳ���
			if (packetTotalLen > m_stream->GetBufLen())//���ܳ��ȳ������ֽڳ�����Ϊ��Ч��
			{
				m_stream->Detele(m_nPackageHeadLen);//ɾ����Ч��ͷ����
				::ReleaseMutex(m_hMutexStream);//����
				OnPackageHeadInvalid();//��ͷ��Ч�¼�����
				continue;//�����´�ѭ��
			}
			BYTE* buf = m_stream->Read(packetTotalLen);//���ֽ��������ж�ȡһ������������,���Ȳ�������NULL
			::ReleaseMutex(m_hMutexStream);//����
			if (buf != NULL)
			{
				//���ջ�����(������)�¼�����
				if (!OnRecvCmpPacket(buf, packetTotalLen))
				{
					delete buf;
					continue;
				}
				if (PreprocessPack(cmd, buf, packetTotalLen))//Ԥ�����
				{
					NotifyRecver(cmd, buf, packetTotalLen);//֪ͨ�ͻ��˽���ҵ����
				}
				else//����ͻ��˴���
				{
					delete buf;
				}
			}
		}
	}

	bool CProtocolClientMgr::PreprocessPack(int cmd, BYTE* buf, int len)
	{
		if (IsAssignedKeepAlive() && cmd == m_nKeepAlive)//�������������������յ�������
		{
			m_nKeepAliveFailCount = 0;//���յ�������
			return false;
		}
		return true;
	}

	void CProtocolClientMgr::NotifyRecver(int cmd, BYTE* buf, int len)
	{
		if (m_lpfnRecvData)
		{
			BYTE* packBuf = new BYTE[len - m_nPackageHeadLen];//���建����
			memcpy(packBuf, buf + m_nPackageHeadLen, len - m_nPackageHeadLen);//���������
			delete buf;
			m_lpfnRecvData(cmd, packBuf, len - m_nPackageHeadLen);//֪ͨ�ͻ���
		}
		else
		{
			delete buf;
		}
	}

	void CProtocolClientMgr::Init(TCHAR* ip, int port, LPOnRecvPack lpfnRecvData, LPOnRecvProtocolEvt lpfnRecvProtocolEvt)
	{
		if (m_stream == NULL)//ֻ��ʼ��һ��
		{
			m_stream = new CByteStream(m_nStreamBufLen);//�������ջ������ֽ�������
			m_lpfnRecvData = lpfnRecvData;
			m_lpfnRecvProtocolEvt = lpfnRecvProtocolEvt;
			m_tcp.Init(ip, port, m_sendType, m_nTcpBufLen, m_nReconnectTimes, m_nReconnectTimeSpan, m_nConnectTimeout, false);
			m_tcp.SetCallbackT(this, &CProtocolClientMgr::OnRecvData, &CProtocolClientMgr::OnRecvTcpEvt);
		}
	}

	//BYTE* CProtocolClientMgr::PacketFromBuf(int type, BYTE buf[], int bufLen, int* packetLen)
	//{
	//	*packetLen = m_nPackageHeadLen + bufLen;
	//	BYTE* data = new BYTE[*packetLen];
	//	BYTE* bufHead = GetPackageHeadBuf(type, bufLen);
	//	memcpy(data, bufHead, m_nPackageHeadLen);//������ͷ����
	//	delete bufHead;
	//	memcpy(data + m_nPackageHeadLen, buf, bufLen);//������������
	//	return data;
	//}

	//BYTE* CProtocolClientMgr::GetDataBuf(BYTE* buf, int len)
	//{
	//	int datalen = GetDataLen(buf, len);
	//	int headlen = GetHeadLen();
	//	BYTE* result = new BYTE[datalen];
	//	memcpy(result, buf + headlen, datalen);
	//	return result;
	//}

	BYTE* CProtocolClientMgr::Pack(PacketBase* data, int * len)
	{
		BYTE* result = NULL;
		int bufPacketLen = 0;
		BYTE* bufPacket = data->Read(&bufPacketLen);//���建����
		if (bufPacket)
		{
			result = new BYTE[bufPacketLen + m_nPackageHeadLen];
			BYTE* bufHead = m_pHead->Read(data->GetCmd(), bufPacketLen);
			memcpy(result, bufHead, m_nPackageHeadLen);//������ͷ������
			memcpy(result + m_nPackageHeadLen, bufPacket, bufPacketLen);//�������建����
			delete bufHead;
			delete bufPacket;
			if (len != NULL)
			{
				*len = m_nPackageHeadLen + bufPacketLen;
			}
		}
		return result;
	}

	bool CProtocolClientMgr::SendPack(PacketBase* data)
	{
		int len = 0;
		BYTE* buf = Pack(data, &len);
		if (buf != NULL)
		{
			OnBeforeSendPack(data->GetCmd(), buf, len);
			bool b = m_tcp.SendData(buf, len);
			delete buf;
			return b;
		}
		return false;
	}

	bool CProtocolClientMgr::SendData(BYTE* buf, int len)
	{
		return m_tcp.SendData(buf, len);
	}

	void CProtocolClientMgr::CloseConnect()
	{
		m_tcp.CloseConnect();
	}

	void CProtocolClientMgr::Connect()
	{
		m_tcp.Connect();
	}

	CTcpClient CProtocolClientMgr::GetTcpClientObj()
	{
		return m_tcp;
	}

	void CProtocolClientMgr::SimulateServerData(PacketBase* data)
	{
		int len = 0;
		BYTE* buf = Pack(data, &len);
		m_tcp.SimulateServerData(buf, len);
		delete buf;
	}

	void CProtocolClientMgr::OnRecvTcpEvt(TcpEvtType type, TCHAR* msg)
	{
		if (type == TcpEvtType::connectsuccess)
		{
			OnTcpConnectSuccess(msg);
		}
		else if (type == TcpEvtType::connfailed)
		{
			OnTcpConnectFail(msg);
		}
		else if (type == TcpEvtType::disconnect)
		{
			OnServerDisconnect(msg);
		}
		else if (type == TcpEvtType::TcpInfo)
		{
			SendProtocolEvt(ProtocolEvtType::Info, msg);
		}
		else
		{
			SendProtocolEvt(ProtocolEvtType::fatal, msg);
		}
	}

	void CProtocolClientMgr::OnTcpConnectSuccess(TCHAR* msg)
	{
		m_stream->Clean();//��տ��ܴ��ڵ�����
		SendProtocolEvt(ProtocolEvtType::tcpsuccess, msg);
	}

	void CProtocolClientMgr::OnTcpConnectFail(TCHAR* msg)
	{
		SendProtocolEvt(ProtocolEvtType::tcpfailed, msg);
	}

	void CProtocolClientMgr::OnServerDisconnect(TCHAR* msg)
	{
		SendProtocolEvt(ProtocolEvtType::serverdis, msg);
		m_stream->Clean();//��տ��ܴ��ڵ�����
		Reconnect();
	}

	void CProtocolClientMgr::StartKeepAlive()
	{
		if (IsAssignedKeepAlive())
		{
			if (m_timer == NULL)
			{
				m_timer = new CTimerT<CProtocolClientMgr>(m_nKeepAliveTimespan);//������ʱ��
				m_timer->SetCallbackT(&CProtocolClientMgr::OnKeepAliveTimeout, this);
			}
			m_nKeepAliveFailCount = -1;
			m_timer->Start();
		}
	}

	bool CProtocolClientMgr::OnKeepAliveTimeout()
	{
		SendPack(m_pKeepAlive);
		if (m_nKeepAliveFailCount <= m_nKeepAliveFailMaxCount)//ʧ�ܴ�����������ʧ�ܴ���
		{
			if (m_nKeepAliveFailCount == 0)//���յ�������,����ʧ�ܴ���Ϊ-1
			{
				m_nKeepAliveFailCount = -1;
			}
			else
			{
				if (m_nKeepAliveFailCount > 0)//�ϴ�δ��⵽������,����Ӧ+1
				{
					m_nKeepAliveFailCount++;
				}
				else//�ϴγɹ���⵽������,����û��⵽������,ʧ�ܴ�������ӦΪ1
				{
					m_nKeepAliveFailCount = 1;
				}
				Printf(_T("check keepalive package failed \n"));
			}
			return true;
		}
		else
		{
			m_nKeepAliveFailCount = -1;
			OnLoseServer();
			return false;
		}
	}

	void CProtocolClientMgr::SendProtocolEvt(ProtocolEvtType type, TCHAR* msg)
	{
		if (m_lpfnRecvProtocolEvt)
		{
			m_lpfnRecvProtocolEvt(type, msg);
		}
		else
		{
			Printf(msg);
		}
	}

	void CProtocolClientMgr::OnLoseServer()
	{
		SendProtocolEvt(ProtocolEvtType::LoseServer, _T("Lose connect with server: %s:%d \n"));
		Reconnect();
	}

	void CProtocolClientMgr::OnBeforeSendPack(int cmd, BYTE* buf, int len)
	{
		Printf(_T("Prepare to send packet to server! \n"));
	}

	bool CProtocolClientMgr::OnRecvCmpPacket(BYTE* buf, int len)
	{
		return true;
	}

	bool CProtocolClientMgr::IsAssignedKeepAlive()
	{
		return m_nKeepAlive != -999;
	}

	void CProtocolClientMgr::OnPackageHeadInvalid()
	{
		Printf(_T(" \n"));
	}

	void CProtocolClientMgr::Reconnect()
	{
		m_tcp.CloseConnect();//�ر�tcp����
		if (m_nReconnectServerMaxCount == 0 ||
			(m_nReconnectServerMaxCount > 0 && m_nReconnectServerCount <= m_nReconnectServerMaxCount))//�����ٴ����ӷ����
		{
			Connect();//�������ӷ����
		}
		else//�ѳ����������ӷ���˴���
		{
			m_nReconnectServerCount++;
		}
	}
}