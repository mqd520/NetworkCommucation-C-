#pragma once

#include <tchar.h>
#include <vector>
#include "MemoryTool.h"
#include "Interface.h"
#include "TcpClientT.h"

namespace NetworkCommunication
{
	template<typename TPackageType, typename TPackageBase>
	//协议管理
	//第1个模板参数:	包类型定义
	//第2个模板参数:	包管理器基类定义
	class CProtocolMgr1
	{
	private:
		//CProtocolMgr重定义
		typedef CProtocolMgr1<TPackageType, TPackageBase>	CProtocolMgrSelf;

	protected:
		//************************************
		// Method:    客户端收到包体数据函数指针
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::LPOnRecvBusinessData
		// Access:    protected 
		// Returns:   void
		// Qualifier: 包类型
		// Parameter: 包体结构体指针
		//************************************
		typedef void(*LPOnRecvPackageBodyData)(TPackageType type, void* data);

		//包管理信息
		typedef struct tagPackageMgrInfo
		{
			TPackageType type;//包类型
			IPackageMgr* mgr;//包管理器
		}PackageMgrInfo, *LPPackageMgrInfo;

	protected:
		CTcpClientT<CProtocolMgr> m_tcp;//tcp客户端对象
		CByteStream* m_stream;//字节流对象
		LPOnRecvPackageBodyData m_lpfnRecvData;//收到数据函数指针
		int m_nPackageHeadLen;//包头长度
		TPackageType m_nKeepAlive;//心跳包类型
		vector<PackageMgrInfo> m_vecPackageMgr;//包管理器集合
		HANDLE m_hMutexStream;//字节流互斥对象

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
		// Method:    关联包类型到包管理器
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::AssoicatePackageType
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void AssociatePackageType()
		{

		};

		//************************************
		// Method:    验证心跳包
		// FullName:  ProtocolMgr::CProtocolMgr<TPackageType, TPackageBase>::ValidateKeepAlivePackage
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		// Parameter: 心跳包
		//************************************
		virtual bool ValidateKeepAlivePackage(TPackageBase* data)
		{
			return true;
		}

		//************************************
		// Method:    验证接收到的包头缓冲区是否有效(缓冲区长度为包头长度)
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::ValidatePackageHead
		// Access:    virtual protected 
		// Returns:   bool
		// Qualifier:
		// Parameter: 缓冲区
		//************************************
		virtual bool ValidatePackageHead(BYTE buf[])
		{
			return false;
		};

		//************************************
		// Method:    验证包类型是否有效
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::ValidatePackageType
		// Access:    virtual protected 
		// Returns:   bool
		// Qualifier:
		// Parameter: 包类型
		//************************************
		virtual bool ValidatePackageType(TPackageType type)
		{
			return false;
		};

		//************************************
		// Method:    接收数据事件处理
		// FullName:  CServer3Mgr::OnRecvData
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual bool OnRecvData(BYTE buf[], int len)
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
		};

		//************************************
		// Method:    开始解包(循环从流中解包,直到流中长度不足包头长度)
		// FullName:  CServer3Mgr::Unpacket
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void StartUnpacket()
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
				TPackageType type = GetPackageType(m_stream->GetBuf(), m_nPackageHeadLen);//获取包类型
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
					if (AnalyticsPackage(type, (TPackageBase*)data))//分析包是否交由调用者处理
					{
						if (m_lpfnRecvData)
						{
							m_lpfnRecvData(type, data);
						}
						else
						{
							ReleasePackage(type, (TPackageBase*)data);//释放包数据
						}
					}
					else
					{
						ReleasePackage(type, (TPackageBase*)data);//释放包数据
					}
				}
			}
		};

		//************************************
		// Method:    分析包,表示是否交由调用者处理包
		// FullName:  CServer3Mgr::AnalyticsPackage
		// Access:    public 
		// Returns:   是否交由调用者处理
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体结构体指针
		//************************************
		virtual bool AnalyticsPackage(TPackageType type, TPackageBase* data)
		{
			if (type == m_nKeepAlive)//心跳包
			{
				bool b = ValidateKeepAlivePackage(data);
				if (!b)
				{
					//重置
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
			if (m_stream == NULL)//只初始化一次
			{
				m_stream = new CByteStream(proBufLen);//创建接收缓冲区字节流对象
				m_lpfnRecvData = lpfnRecvData;
				AssociatePackageType();//关联包类型和包管理器
				m_tcp.Init(ip, port, lpfnNotifyEvt, tcpBufLen, autoReconnect, reconnectTimes, reconnectTimeSpan, connectTimeout);
				m_tcp.SetCallbackT(&CProtocolMgrSelf::OnRecvData, this);//设置成员函数回调
				return m_tcp.Connect();
			}
		};

		//************************************
		// Method:    封包(调用方释放缓冲区指针)
		// FullName:  Protocol3::CProtocol3Handle::Packet
		// Access:    public 
		// Returns:   包缓冲区指针
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体数据缓冲区指针
		// Parameter: 包体数据缓冲区长度
		// Parameter: 包缓冲区长度(输出)
		//************************************
		virtual BYTE* PacketFromBuf(TPackageType type, BYTE buf[], int bufLen, int* packetLen)
		{
			*packetLen = m_nPackageHeadLen + bufLen;
			BYTE* data = new BYTE[*packetLen];
			BYTE* bufHead = GetPackageHeadBuf(type, bufLen);
			memcpy(data, bufHead, m_nPackageHeadLen);//拷贝包头数据
			delete bufHead;
			memcpy(data + m_nPackageHeadLen, buf, bufLen);//拷贝包体数据
			return data;
		};

		//************************************
		// Method:    获取包头缓冲区
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::GetPackageHeadBuf
		// Access:    virtual protected 
		// Returns:   缓冲区
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体数据长度
		//************************************
		virtual BYTE* GetPackageHeadBuf(TPackageType type, int len)
		{
			return NULL;
		};

		//************************************
		// Method:    封包(调用方释放缓冲区指针)
		// FullName:  Protocol3::CProtocol3Handle::Packet
		// Access:    public static 
		// Returns:   包缓冲区指针
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体结构体指针
		// Parameter: 包缓冲区长度(输出)
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
		// Method:    从缓冲区中(包含包头和包体)解析出一个包体结构体数据
		// FullName:  Protocol3::CProtocol3Handle::Unpacket
		// Access:    public 
		// Returns:   包体结构体指针
		// Qualifier:
		// Parameter: 完整包缓冲区指针
		// Parameter: 缓冲区长度
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
		// Method:    获取包头长度
		// FullName:  Protocol3::CProtocol3Handle::GetHeadLen
		// Access:    public 
		// Returns:   包头长度
		// Qualifier:
		//************************************
		virtual int GetHeadLen()
		{
			return m_nPackageHeadLen;
		};

		//************************************
		// Method:    从缓冲区中获取包体数据长度
		// FullName:  Protocol3::CProtocol3Handle::GetDataLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区长度
		//************************************
		virtual int GetDataLen(BYTE buf[], int len)
		{
			return m_nPackageHeadLen;
		};

		//************************************
		// Method:    从缓冲区中获取包类型
		// FullName:  Protocol3::CProtocol3Handle::GetPackageType
		// Access:    public 
		// Returns:   包类型
		// Qualifier:
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区长度
		//************************************
		virtual TPackageType GetPackageType(BYTE buf[], int len)
		{
			return TPackageType(-999);
		};

		//************************************
		// Method:    获取包管理器(调用方无需释放指针)
		// FullName:  Protocol3::CProtocol3Handle::GetMgr
		// Access:    protected static 
		// Returns:   Protocol3::Package3Mgr*
		// Qualifier:
		// Parameter: 包类型
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
		// Method:    获取包体缓冲区指针
		// FullName:  Protocol3::CProtocol3Handle::GetDataBuf
		// Access:    public static 
		// Returns:   包体缓冲区指针
		// Qualifier:
		// Parameter: 包缓冲区指针 
		// Parameter: 包缓冲区长度
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
		// Method:    释放包体结构体
		// FullName:  CServer3Mgr::ReleasePackage
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体结构体指针
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
		// Method:    发包
		// FullName:  CServer3Mgr::Send
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体结构体指针
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
		// Method:    关闭连接
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
		// Method:    连接服务端
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
		// Method:    获取tcp客户端对象
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
		// Method:    模拟一次服务端发包
		// FullName:  CServer3Mgr::SimulateServer3Data
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体结构体指针
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