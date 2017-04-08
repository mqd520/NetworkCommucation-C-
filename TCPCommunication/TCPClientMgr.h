#pragma once

#include <tchar.h>
#include <vector>
#include "MemoryTool.h"
#include "ProtocolMgr.h"
#include "SocketClient.h"

using namespace ProtocolMgr;
using namespace MemoryTool;

namespace TCPCLientMgr
{
	template<typename TPackageType, typename TPackageBase, typename TProtocolMgr>
	//第1个模板参数:	包类型定义
	//第2个模板参数:	包基类型定义
	//第3个模板参数:	CProtocolMgr类型或者CProtocolMgr的派生类
	class CTCPClientMgr
	{
	public:
		//函数指针:收到业务数据
		typedef void(*LPOnRecvBusinessData)(TPackageType type, void* data);

	protected:


	protected:
		CSocketClient m_tcp;//tcp客户端管理对象
		TProtocolMgr m_protocol;//协议管理对象
		CByteStream* m_stream;//字节流对象
		CByteStream* m_streamCatch;//字节流缓存对象
		LPOnRecvBusinessData m_lpfn;//业务数据函数指针
		LPOnRecvTCPData m_lpfnTcp;//tcp数据函数指针 

	public:
		CTCPClientMgr()
		{
			m_lpfnTcp = NULL;
			m_streamCatch = NULL;
			m_lpfn = NULL;
			m_stream = new CByteStream(1024);
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
			m_tcp.Dispose();
		};

		//************************************
		// Method:    初始化
		// FullName:  CServer3Mgr::Init
		// Access:    public static 
		// Returns:   bool
		// Qualifier:
		// Parameter: TCHAR * ip
		// Parameter: int port
		//************************************
		virtual bool Init(TCHAR* ip, int port, LPOnRecvBusinessData lpfn, LPOnRecvTCPData lpfnTcp)
		{
			m_lpfn = lpfn;
			m_lpfnTcp = lpfnTcp;
			m_protocol.Init();
			m_tcp.Init(ip, port, m_lpfnTcp);
			m_tcp.StartConnect();
			return true;
		};

		//************************************
		// Method:    接收数据事件处理
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
				m_stream->Write(m_streamCatch);//从缓存中读取数据写入到当前流对象
				if (m_streamCatch->GetDataLen() == 0)//缓存流对象不再使用
				{
					delete m_streamCatch;
					m_streamCatch = NULL;
				}
				else
				{
					if (len > 0)
					{
						m_streamCatch->Write(buf, len);//buf来源于服务端,将buf存储于缓存流中
					}
					Unpacket();
					OnRecvData(NULL, 0);//继续从缓存流中读取数据
				}
			}
			if (len > 0)//buf来源于服务端
			{
				int len1 = m_stream->Write(buf, len);//实际写入的长度
				Unpacket();
				if (len1 < len)
				{
					m_streamCatch = new CByteStream(len - len1);//流对象未能全部存储数据,需要缓存流对象存储数据
					m_streamCatch->Write(buf + len1, len - len1);
					OnRecvData(NULL, 0);//继续从缓存流中读取数据
				}
			}
			else
			{
				Unpacket();
			}
		};

		//************************************
		// Method:    解包
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
				TPackageType type = m_protocol.GetPackageType(m_stream->GetBuf(), headlen);//获取包类型
				if ((int)type != m_protocol.GetInvalidPackage())
				{
					int datalen = m_protocol.GetDataLen(m_stream->GetBuf(), headlen);//获取包体数据长度
					int packgetlen = datalen + headlen;//计算包总长度
					BYTE* buf = m_stream->Read(packgetlen);//从字节流对象中读取一个完整包数据
					if (buf != NULL)
					{
						void* data = m_protocol.Unpacket(buf, packgetlen);//解包
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
		// Method:    分析包,表示是否需要继续处理
		// FullName:  CServer3Mgr::AnalyticsPackage
		// Access:    public 
		// Returns:   否需要继续处理
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体结构体指针
		//************************************
		virtual bool AnalyticsPackage(TPackageType type, TPackageBase* data)
		{
			if (type == m_protocol.GetKeepAlivePackage())//心跳包
			{
				bool b = m_protocol.ValidateKeepAlivePackage(data);
				if (!b)
				{
					//重置
				}
				return true;
			}
			return true;
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
			CProtocolMgr<TPackageType, TPackageBase>::ParserInfo parser = m_protocol.GetPacketParser(type);
			if (parser.release)
			{
				parser.release(data);
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
		virtual bool Send(TPackageType type, TPackageBase* data)
		{
			int len = 0;
			BYTE* buf = m_protocol.PacketFromData(type, data, &len);
			return m_tcp.SendData(buf, len);
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
		virtual void SimulateServer3Data(TPackageType type, TPackageBase* data)
		{
			int len = 0;
			BYTE* buf = m_protocol.PacketFromData(type, data, &len);
			m_tcp.OnRecvData(buf, len);
			delete buf;
		};
	};
}