#include "stdafx.h"
#include "ProtocolMgr.h"

#define PackageTypeNullVal	(-999)//包类型空值,表示没有设置

namespace NetworkCommunication
{
	//开始心跳包线程
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
		m_nKeepAliveFailMaxCount(3),
		m_pKeepAlive(NULL),
		m_pKeepAliveBuf(NULL),
		m_nKeepAliveBufLen(0)
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
		if (m_pKeepAliveBuf)
		{
			delete m_pKeepAliveBuf;
			m_pKeepAliveBuf = NULL;
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

	void CProtocolMgr::StartUnpacket()
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
			if (!ValidatePackageHead(m_stream->GetBuf()))//验证包头是否有效
			{
				m_stream->Detele(m_nPackageHeadLen);//删除无效包头数据
				::ReleaseMutex(m_hMutexStream);//解锁
				continue;//继续下次循环
			}
			int type = GetPackageType(m_stream->GetBuf(), m_nPackageHeadLen);//获取包类型
			if (!ValidatePackageType(type))
			{
				m_stream->Detele(m_nPackageHeadLen);//删除无效包头数据
				::ReleaseMutex(m_hMutexStream);//解锁
				continue;//继续下次循环
			}
			int datalen = GetDataLen(m_stream->GetBuf(), m_nPackageHeadLen);//获取包体数据长度
			int packgetlen = datalen + m_nPackageHeadLen;//计算包总长度
			if (packgetlen > m_stream->GetBufLen())//包总长度超过流字节长度视为无效包
			{
				m_stream->Detele(m_nPackageHeadLen);//删除无效包头数据
				::ReleaseMutex(m_hMutexStream);//解锁
				continue;//继续下次循环
			}
			BYTE* buf = m_stream->Read(packgetlen);//从字节流对象中读取一个完整包数据
			::ReleaseMutex(m_hMutexStream);//解锁
			if (buf != NULL)
			{
				void* data = Unpacket(buf, packgetlen);//解包
				delete buf;
				if (AnalyticsPackage(type, (LPPackageBase)data))//分析包是否交由调用者处理
				{
					if (m_lpfnRecvData)
					{
						m_lpfnRecvData(type, (LPPackageBase)data);
					}
					else
					{
						ReleasePackage(type, (LPPackageBase)data);//释放包数据
					}
				}
				else
				{
					ReleasePackage(type, (LPPackageBase)data);//释放包数据
				}
			}
		}
	}

	bool CProtocolMgr::AnalyticsPackage(int type, LPPackageBase data)
	{
		if (type == m_nKeepAlive&&m_nKeepAlive != PackageTypeNullVal)//启用了心跳包并且已收到心跳包
		{
			bool b = ValidateKeepAlivePackage(data);
			if (b)
			{
				m_nKeepAliveFailCount = 0;//已收到心跳包
			}
			return false;
		}
		return true;
	}

	void CProtocolMgr::Init(TCHAR* ip, int port, LPOnRecvPackageBodyData lpfnRecvData, LPOnRecvNotifyEvt lpfnNotifyEvt, int proBufLen,
		int tcpBufLen, bool autoReconnect, int reconnectTimes, int reconnectTimeSpan, int connectTimeout)
	{
		if (m_stream == NULL)//只初始化一次
		{
			m_stream = new CByteStream(proBufLen);//创建接收缓冲区字节流对象
			m_lpfnRecvData = lpfnRecvData;
			AssociatePackageType();//关联包类型和包管理器
			InitKeepAlive();//初始化心跳包
			m_tcp.Init(ip, port, lpfnNotifyEvt, tcpBufLen, autoReconnect, reconnectTimes, reconnectTimeSpan, connectTimeout);
			m_tcp.SetCallbackT(&CProtocolMgr::OnRecvData, this);//设置成员函数回调
			return m_tcp.Connect();
		}
	}

	BYTE* CProtocolMgr::PacketFromBuf(int type, BYTE buf[], int bufLen, int* packetLen)
	{
		*packetLen = m_nPackageHeadLen + bufLen;
		BYTE* data = new BYTE[*packetLen];
		BYTE* bufHead = GetPackageHeadBuf(type, bufLen);
		memcpy(data, bufHead, m_nPackageHeadLen);//拷贝包头数据
		delete bufHead;
		memcpy(data + m_nPackageHeadLen, buf, bufLen);//拷贝包体数据
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
		m_tcp.Connect();
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
			if (IsOnline())//如果对方在线,则验证对方是否在线并向对方发送心跳包
			{
				bool b = true;//是否向对方发送心跳包
				if (m_nKeepAliveFailCount > 0)//没有收到心跳包
				{
					if (m_nKeepAliveFailCount > m_nKeepAliveFailMaxCount)//超过允许失败最大值
					{
						b = false;//认为对方已掉线
					}
					else
					{
						m_nKeepAliveFailCount++;
					}
				}
				else//如果收到了心跳包,立即设置为没有收到心跳包状态
				{
					m_nKeepAliveFailCount = 1;
				}
				if (b&&m_pKeepAlive)
				{
					m_tcp.SendData(m_pKeepAliveBuf, m_nKeepAliveBufLen);//向对方发送心跳包
				}
			}
			else
			{
				OutputDebugString(_T("对方已掉线\n"));
			}

			::Sleep(m_nKeepAliveTimeout);
		}
	}

	bool CProtocolMgr::IsOnline()
	{
		if (m_nKeepAlive != PackageTypeNullVal)//指示启用了心跳包
		{
			//通过判断接收心跳包失败次数是否超过最大值来决定是否在线
			return m_nKeepAliveFailCount > m_nKeepAliveFailMaxCount ? false : true;
		}
		else
		{
			//通过向对方发送TCP数据是否成功来判断是否在线
			BYTE buf[1] = { 0 };
			return 	m_tcp.SendData(buf, 1);
		}
	}

	void CProtocolMgr::InitKeepAlive()
	{
		if (m_nKeepAlive != PackageTypeNullVal&&m_pKeepAlive)//客户端指定了心跳包
		{
			IPackageMgr* mgr = GetPackageMgr(m_nKeepAlive);
			if (mgr)
			{
				m_pKeepAliveBuf = Packet(m_nKeepAlive, m_pKeepAlive, &m_nKeepAliveBufLen);
				m_tiTimer.hThread = ::CreateThread(NULL, 0, StartTimer, this, NULL, &(m_tiTimer.dwThreadID));
			}
		}
	}

	DWORD WINAPI StartTimer(LPVOID lpParam)
	{
		CProtocolMgr* mgr = (CProtocolMgr*)lpParam;
		mgr->OnTimerKeepAlive();
		return 0;
	}
}