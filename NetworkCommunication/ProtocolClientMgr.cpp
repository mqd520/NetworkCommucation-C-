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
		m_lpfnRecvProtocolEvt(NULL),
		m_nStreamBufLen(1024),
		m_nTcpBufLen(1024),
		m_bAutoReconnect(true),
		m_nReconnectTimes(0),
		m_nReconnectTimeSpan(2000),
		m_nConnectTimeout(2000),
		m_sendType(TcpDataRecvType::single),
		m_pHead(NULL),
		m_nServerPort(0),
		m_timer(NULL)
	{
		m_hMutexStream = ::CreateMutex(NULL, false, NULL);
		memset(m_strServerIP, 0, 20);
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
			TCHAR str[50];
			wsprintf(str, _T("Recive keepalive packet: %s:%d \n"), m_strServerIP, m_nServerPort);
			Printf(str);
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
#ifdef _UNICODE
			wcscpy((wchar_t*)m_strServerIP, ip);
#else
			strcpy((char*)m_strServerIP, ip);
#endif // _UNICODE
			m_nServerPort = port;
			m_nPackageHeadLen = m_pHead->GetHeadLen();
			m_stream = new CByteStream(m_nStreamBufLen);//�������ջ������ֽ�������
			m_lpfnRecvData = lpfnRecvData;
			m_lpfnRecvProtocolEvt = lpfnRecvProtocolEvt;
			m_tcp.Init(ip, port, m_sendType, m_nTcpBufLen, m_nReconnectTimes, m_nReconnectTimeSpan, m_nConnectTimeout, false);
			m_tcp.SetCallbackT(this, &CProtocolClientMgr::OnRecvData, &CProtocolClientMgr::OnRecvTcpEvt);
		}
	}

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
			SendKeepAlivePack();//����������
			m_timer->Start();
		}
	}

	bool CProtocolClientMgr::OnKeepAliveTimeout()
	{
		if (m_nKeepAliveFailCount < m_nKeepAliveFailMaxCount)//ʧ�ܴ�����������ʧ�ܴ���
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
				TCHAR str[50];
				wsprintf(str, _T("Check keepalive package failed: %s:%d \n"), m_strServerIP, m_nServerPort);
				Printf(str);
			}
			SendKeepAlivePack();//����������
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
		TCHAR str[50];
		wsprintf(str, _T("Lose connect with server: %s:%d \n"), m_strServerIP, m_nServerPort);
		SendProtocolEvt(ProtocolEvtType::LoseServer, str);
		Reconnect();
	}

	void CProtocolClientMgr::OnBeforeSendPack(int cmd, BYTE* buf, int len)
	{
		TCHAR str[50];
		wsprintf(str, _T("Prepare to send packet to server: %s:%d \n"), m_strServerIP, m_nServerPort);
		Printf(str);
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

	void CProtocolClientMgr::SendKeepAlivePack()
	{
		TCHAR str[50];
		wsprintf(str, _T("Send keepalive packet: %s:%d \n"), m_strServerIP, m_nServerPort);
		Printf(str);
		SendPack(m_pKeepAlive);
	}
}