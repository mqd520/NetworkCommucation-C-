#pragma once

#include <vector>
#include "Package3.h"
#include "Package3Mgr.h"

using namespace std;

namespace Protocol3
{
	//解析器信息
	typedef struct tagParserInfo
	{
		LPPackage3Unparse	unparse;//反解析器
		LPPackage3Parse		parse;//解析器
		LPPackage3Release	release;//释放器
	}ParserInfo, *LPParserInfo;

	//协议管理
	class CProtocolMgr
	{
	public:
		CProtocolMgr(){};
		~CProtocolMgr(){};

		//************************************
		// Method:    初始化
		// FullName:  Protocol3::CProtocol3Handle::Init
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void Init();

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
		BYTE* Packet(Package3Type type, BYTE buf[], int bodyLen, int* packetLen);

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
		BYTE* Packet(Package3Type type, LPPackage3Base data, int* packetLen);

		//************************************
		// Method:    从一个完整包缓冲区中解析一个包体数据
		// FullName:  Protocol3::CProtocol3Handle::Unpacket
		// Access:    public 
		// Returns:   包体结构体指针
		// Qualifier:
		// Parameter: 完整包缓冲区指针
		// Parameter: 缓冲区长度
		//************************************
		void* Unpacket(BYTE buf[], int len);

		//************************************
		// Method:    获取包头长度
		// FullName:  Protocol3::CProtocol3Handle::GetHeadLen
		// Access:    public 
		// Returns:   包头长度
		// Qualifier:
		//************************************
		int GetHeadLen();

		//************************************
		// Method:    从缓冲区中获取包体数据长度
		// FullName:  Protocol3::CProtocol3Handle::GetDataLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区长度
		//************************************
		int GetDataLen(BYTE buf[], int len);

		//************************************
		// Method:    从缓冲区中获取包类型
		// FullName:  Protocol3::CProtocol3Handle::GetPackageType
		// Access:    public 
		// Returns:   包类型
		// Qualifier:
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区长度
		//************************************
		Package3Type GetPackageType(BYTE buf[], int len);

		//************************************
		// Method:    获取包解析器(调用方无需释放指针)
		// FullName:  Protocol3::CProtocol3Handle::GetMgr
		// Access:    protected static 
		// Returns:   Protocol3::Package3Mgr*
		// Qualifier:
		// Parameter: 包类型
		//************************************
		ParserInfo GetPacketParser(Package3Type type);

		//************************************
		// Method:    获取包体缓冲区指针
		// FullName:  Protocol3::CProtocol3Handle::GetDataBuf
		// Access:    public static 
		// Returns:   包体缓冲区指针
		// Qualifier:
		// Parameter: 包缓冲区指针 
		// Parameter: 包缓冲区长度
		//************************************
		BYTE* GetDataBuf(BYTE* buf, int len);

	protected:
		//Package3包解析信息
		typedef struct tagPackage3ParseInfo
		{
			Package3Type type;//包类型
			ParserInfo	parser;//解析器信息
		}Package3ParseInfo, *LPPackage3ParseInfo;

		vector<Package3ParseInfo> m_vecParserList;//包解析器集合
	};
}