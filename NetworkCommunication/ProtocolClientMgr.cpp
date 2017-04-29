#include "stdafx.h"
#include "ProtocolClientMgr.h"

#define PackageTypeNullVal	(-999)//包类型空值,表示没有设置

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
		int index = 0;//读取缓冲区开始索引
		while (true)
		{
			::WaitForSingleObject(m_hMutexStream, INFINITE);
			int actualLen = m_stream->Write(buf + index, len);//缓冲区数据写入到流对象,返回实际写入字节长度
			if (m_stream->IsFull())//如果流中数据已满,立刻进行解包操作
			{
				::ReleaseMutex(m_hMutexStream);
				StartUnpacket();
			}
			else
			{
				if (actualLen < len)//实际读取长度小于缓冲区长度,继续循环读取缓冲区
				{
					index += actualLen;
					::ReleaseMutex(m_hMutexStream);
					continue;
				}
				else//缓冲区数据已读取完毕,跳出循环,进行解包操作
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
			::WaitForSingleObject(m_hMutexStream, INFINITE);//锁住互斥对象

			//数据长度小于等于包头长度(表示流中没有包体数据,不进行任何处理,继续接收数据)
			if (m_stream->GetDataLen() <= m_nPackageHeadLen)
			{
				::ReleaseMutex(m_hMutexStream);//解锁
				break;
			}
			m_pHead->Write(m_stream->GetBuf(), m_nPackageHeadLen);//写入缓冲区到包头
			if (!m_pHead->IsValid())//验证包头是否有效
			{
				m_stream->Detele(m_nPackageHeadLen);//删除无效包头数据
				::ReleaseMutex(m_hMutexStream);//解锁
				OnPackageHeadInvalid();//包头无效事件处理
				continue;//继续下次循环
			}
			int cmd = m_pHead->GetCmd();//获取包命令
			int packetLen = m_pHead->GetPacketLen();//获取包体数据长度
			int packetTotalLen = packetLen + m_nPackageHeadLen;//获取包总长度
			if (packetTotalLen > m_stream->GetBufLen())//包总长度超过流字节长度视为无效包
			{
				m_stream->Detele(m_nPackageHeadLen);//删除无效包头数据
				::ReleaseMutex(m_hMutexStream);//解锁
				OnPackageHeadInvalid();//包头无效事件处理
				continue;//继续下次循环
			}
			BYTE* buf = m_stream->Read(packetTotalLen);//从字节流对象中读取一个完整包数据,长度不够返回NULL
			::ReleaseMutex(m_hMutexStream);//解锁
			if (buf != NULL)
			{
				//接收缓冲区(完整包)事件处理
				if (!OnRecvCmpPacket(buf, packetTotalLen))
				{
					delete buf;
					continue;
				}
				if (PreprocessPack(cmd, buf, packetTotalLen))//预处理包
				{
					NotifyRecver(cmd, buf, packetTotalLen);//通知客户端进行业务处理
				}
				else//无需客户端处理
				{
					delete buf;
				}
			}
		}
	}

	bool CProtocolClientMgr::PreprocessPack(int cmd, BYTE* buf, int len)
	{
		if (IsAssignedKeepAlive() && cmd == m_nKeepAlive)//启用了心跳包并且已收到心跳包
		{
			m_nKeepAliveFailCount = 0;//已收到心跳包
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
			BYTE* packBuf = new BYTE[len - m_nPackageHeadLen];//包体缓冲区
			memcpy(packBuf, buf + m_nPackageHeadLen, len - m_nPackageHeadLen);//分离出包体
			delete buf;
			m_lpfnRecvData(cmd, packBuf, len - m_nPackageHeadLen);//通知客户端
		}
		else
		{
			delete buf;
		}
	}

	void CProtocolClientMgr::Init(TCHAR* ip, int port, LPOnRecvPack lpfnRecvData, LPOnRecvProtocolEvt lpfnRecvProtocolEvt)
	{
		if (m_stream == NULL)//只初始化一次
		{
#ifdef _UNICODE
			wcscpy((wchar_t*)m_strServerIP, ip);
#else
			strcpy((char*)m_strServerIP, ip);
#endif // _UNICODE
			m_nServerPort = port;
			m_nPackageHeadLen = m_pHead->GetHeadLen();
			m_stream = new CByteStream(m_nStreamBufLen);//创建接收缓冲区字节流对象
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
		BYTE* bufPacket = data->Read(&bufPacketLen);//包体缓冲区
		if (bufPacket)
		{
			result = new BYTE[bufPacketLen + m_nPackageHeadLen];
			BYTE* bufHead = m_pHead->Read(data->GetCmd(), bufPacketLen);
			memcpy(result, bufHead, m_nPackageHeadLen);//拷贝包头缓冲区
			memcpy(result + m_nPackageHeadLen, bufPacket, bufPacketLen);//拷贝包体缓冲区
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
		m_stream->Clean();//清空可能存在的数据
		SendProtocolEvt(ProtocolEvtType::tcpsuccess, msg);
	}

	void CProtocolClientMgr::OnTcpConnectFail(TCHAR* msg)
	{
		SendProtocolEvt(ProtocolEvtType::tcpfailed, msg);
	}

	void CProtocolClientMgr::OnServerDisconnect(TCHAR* msg)
	{
		SendProtocolEvt(ProtocolEvtType::serverdis, msg);
		m_stream->Clean();//清空可能存在的数据
		Reconnect();
	}

	void CProtocolClientMgr::StartKeepAlive()
	{
		if (IsAssignedKeepAlive())
		{
			if (m_timer == NULL)
			{
				m_timer = new CTimerT<CProtocolClientMgr>(m_nKeepAliveTimespan);//创建定时器
				m_timer->SetCallbackT(&CProtocolClientMgr::OnKeepAliveTimeout, this);
			}
			m_nKeepAliveFailCount = -1;
			SendKeepAlivePack();//发送心跳包
			m_timer->Start();
		}
	}

	bool CProtocolClientMgr::OnKeepAliveTimeout()
	{
		if (m_nKeepAliveFailCount < m_nKeepAliveFailMaxCount)//失败次数低于允许失败次数
		{
			if (m_nKeepAliveFailCount == 0)//已收到心跳包,重置失败次数为-1
			{
				m_nKeepAliveFailCount = -1;
			}
			else
			{
				if (m_nKeepAliveFailCount > 0)//上次未检测到心跳包,本次应+1
				{
					m_nKeepAliveFailCount++;
				}
				else//上次成功检测到心跳包,本次没检测到心跳包,失败次数计数应为1
				{
					m_nKeepAliveFailCount = 1;
				}
				TCHAR str[50];
				wsprintf(str, _T("Check keepalive package failed: %s:%d \n"), m_strServerIP, m_nServerPort);
				Printf(str);
			}
			SendKeepAlivePack();//发送心跳包
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
		m_tcp.CloseConnect();//关闭tcp连接
		if (m_nReconnectServerMaxCount == 0 ||
			(m_nReconnectServerMaxCount > 0 && m_nReconnectServerCount <= m_nReconnectServerMaxCount))//允许再次连接服务端
		{
			Connect();//重新连接服务端
		}
		else//已超过允许连接服务端次数
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