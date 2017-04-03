#pragma once

#include "Package3.h"

namespace Protocol3
{
	class CProtocol3Handle
	{
	public:
		CProtocol3Handle();
		~CProtocol3Handle();

		//************************************
		// Method:    封包,调用者释放内存
		// FullName:  Protocol3::CProtocol3Handle::Packet
		// Access:    public 
		// Returns:   BYTE*
		// Qualifier:
		// Parameter: 包类类型
		// Parameter: 包体数据缓冲区指针
		// Parameter: 缓冲区长度
		//************************************
		BYTE* Packet(Package3Type type, BYTE buf[], int len);

		void* Unpacket(BYTE buf[], int len, Package3Type type);

		//************************************
		// Method:    获取包头长度
		// FullName:  Protocol3::CProtocol3Handle::GetHeadLen
		// Access:    public 
		// Returns:   包头长度
		// Qualifier:
		//************************************
		int GetHeadLen();

		//************************************
		// Method:    从一个完整包缓冲区中获取包体数据长度
		// FullName:  Protocol3::CProtocol3Handle::GetDataLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: 一个完整包的字节数组
		// Parameter: 字节数组长度
		//************************************
		int GetDataLen(BYTE buf[], int len);

		//************************************
		// Method:    从一个完整包缓冲区中获取包类型
		// FullName:  Protocol3::CProtocol3Handle::GetPackageType
		// Access:    public 
		// Returns:   包类型
		// Qualifier:
		// Parameter: 一个完整包的字节数组
		// Parameter: 字节数组长度
		//************************************
		Package3Type GetPackageType(BYTE buf[], int len);

	protected:
		//************************************
		// Method:    解析数据,用于连续内存的包体数据结构
		// FullName:  Protocol3::CProtocol3Handle::Parse
		// Access:    protected 
		// Returns:   包体数据结构指针(需要调用者释放)
		// Qualifier:
		// Parameter: 一个完整包的字节数组
		// Parameter: 字节数组长度
		//************************************
		template<typename T>
		T* Parse(BYTE buf[], int len);
	};
}