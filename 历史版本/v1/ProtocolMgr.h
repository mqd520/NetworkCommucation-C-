#pragma once

#include <vector>
#include "ProtocolTool.h"

using namespace std;
using namespace ProtocolTool;

namespace ProtocolMgr
{
	//协议管理
	template<typename TPackageType, typename TPackageBase>
	//第1个模板参数:	包类型定义
	//第2个模板参数:	包基类型定义
	class CProtocolMgr
	{
	protected:
		//包反解析指针
		typedef BYTE* (*LPPackageUnparse)(TPackageBase* data, int* len);
		//包解析指针
		typedef TPackageBase* (*LPPackageParse)(BYTE* buf, int len);
		//包释放指针
		typedef void(*LPPackageRelease)(TPackageBase* data);

	public:
		//解析器信息
		typedef struct tagParserInfo
		{
			LPPackageUnparse	unparse;//反解析器
			LPPackageParse		parse;//解析器
			LPPackageRelease	release;//释放器
		}ParserInfo, *LPParserInfo;

	protected:
		//包解析信息
		typedef struct tagPackageParseInfo
		{
			TPackageType type;//包类型
			ParserInfo	parser;//解析器信息
		}PackageParseInfo, *LPPackageParseInfo;

	protected:
		int m_nPackageHeadLen;//包头长度
		int m_nInvalidPackage;//无效包
		int m_nKeepAlive;//心跳包
		vector<PackageParseInfo> m_vecParserList;//包解析器集合

	public:
		CProtocolMgr()
		{
			m_nPackageHeadLen = 0;
			m_nInvalidPackage = 0;
			m_nKeepAlive = 0;
		};
		~CProtocolMgr(){};

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
		virtual BYTE* PacketFromData(TPackageType type, TPackageBase* data, int* packetLen)
		{
			CProtocolMgr<TPackageType, TPackageBase>::ParserInfo parser = GetPacketParser(type);
			if (parser.parse)
			{
				int len = 0;
				BYTE* buf = parser.unparse(data, &len);
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
				CProtocolMgr<TPackageType, TPackageBase>::ParserInfo parser = GetPacketParser(type);
				p = (TPackageBase*)parser.parse(buf + m_nPackageHeadLen, len - m_nPackageHeadLen);
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
		// Method:    获取包解析器(调用方无需释放指针)
		// FullName:  Protocol3::CProtocol3Handle::GetMgr
		// Access:    protected static 
		// Returns:   Protocol3::Package3Mgr*
		// Qualifier:
		// Parameter: 包类型
		//************************************
		virtual ParserInfo GetPacketParser(TPackageType type)
		{
			CProtocolMgr<TPackageType, TPackageBase>::ParserInfo p = { 0 };
			for (vector<PackageParseInfo>::iterator it = m_vecParserList.begin(); it < m_vecParserList.end(); ++it)
			{
				if (it->type == type)
				{
					p = it->parser;
					break;
				}
			}
			return p;
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