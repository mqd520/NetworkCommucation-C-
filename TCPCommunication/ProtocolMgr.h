#pragma once

#include <vector>
#include "ProtocolTool.h"

using namespace std;

namespace TCPCommunication
{
	//协议管理
	template<typename TPackageType, typename TPackageBase>
	//第1个模板参数:	包类型定义
	//第2个模板参数:	包基类型定义
	class CProtocolMgr
	{
	protected:
		//包管理信息
		typedef struct tagPackageMgrInfo
		{
			TPackageType type;//包类型
			IPackageMgr* mgr;//包管理器
		}PackageMgrInfo, *LPPackageMgrInfo;

	protected:
		int m_nPackageHeadLen;//包头长度
		int m_nInvalidPackage;//无效包
		int m_nKeepAlive;//心跳包
		vector<PackageMgrInfo> m_vecPackageMgr;//包管理器集合

	public:
		CProtocolMgr()
		{
			m_nPackageHeadLen = 0;
			m_nInvalidPackage = 0;
			m_nKeepAlive = 0;
		};

		~CProtocolMgr()
		{
			for (vector<PackageMgrInfo>::iterator it = m_vecPackageMgr.begin(); it < m_vecPackageMgr.end(); ++it)
			{
				if (it->mgr)
				{
					delete it->mgr;
				}
			}
		};

		//************************************
		// Method:    初始化
		// FullName:  Protocol3::CProtocol3Handle::Init
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Init(){};

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
		virtual BYTE* PacketFromBuf(TPackageType type, BYTE buf[], int bodyLen, int* packetLen)
		{
			*packetLen = bodyLen;
			return buf;
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
				p = (TPackageBase*)mgr->Parse(buf + m_nPackageHeadLen, len - m_nPackageHeadLen);
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
			if (len + 1 > m_nPackageHeadLen)
			{
				return MergeByte(buf[6], buf[5]);
			}
			else
			{
				return 0;
			}
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
			if (len + 1 > m_nPackageHeadLen)
			{
				int type = MergeByte(buf[4], buf[3]);
				return TPackageType(type);
			}
			else
			{
				return TPackageType(m_nPackageHeadLen);
			}
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
		// Method:    获取无效包
		// FullName:  ProtocolMgr::CProtocolMgr<TPackageType, TPackageBase>::GetInvalidPackage
		// Access:    virtual public 
		// Returns:   int
		// Qualifier:
		//************************************
		virtual int GetInvalidPackage()
		{
			return m_nInvalidPackage;
		};

		//************************************
		// Method:    获取心跳包
		// FullName:  ProtocolMgr::CProtocolMgr<TPackageType, TPackageBase>::GetKeepAlivePackage
		// Access:    virtual public 
		// Returns:   int
		// Qualifier:
		//************************************
		virtual int GetKeepAlivePackage()
		{
			return m_nKeepAlive;
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
	};
}