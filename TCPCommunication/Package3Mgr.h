#pragma once

#include "Package3.h"

namespace PackageMgr
{
	//Package3包反解析指针
	typedef BYTE* (*LPPackage3Unparse)(LPPackage3Base data, int* len);
	//Package3包解析指针
	typedef LPPackage3Base(*LPPackage3Parse)(BYTE* buf, int len);
	//Package3包释放指针
	typedef void(*LPPackage3Release)(LPPackage3Base data);

	class CPackage3Mgr
	{
	private:
		CPackage3Mgr(){};
	public:
		~CPackage3Mgr(){};

		//************************************
		// Method:    package3通用反解析
		// FullName:  Protocol3::CPackage3Mgr::CommonUnparse
		// Access:    public static 
		// Returns:   包体缓冲区指针
		// Qualifier:
		// Parameter: 包体结构体指针
		// Parameter: 包体缓冲区长度(输出)
		//************************************
		template<typename T>
		static BYTE* CommonUnparse(LPPackage3Base data, int* len)
		{
			*len = sizeof(T);
			BYTE* buf = new BYTE[*len];
			memcpy(buf, data, *len);
			return buf;
		};

		//************************************
		// Method:    package3通用解析
		// FullName:  Protocol3::CPackage3Mgr::CommonParse
		// Access:    public static 
		// Returns:   包体结构体指针
		// Qualifier:
		// Parameter: 包体缓冲区指针
		// Parameter: 包体缓冲区长度
		//************************************
		template<typename T>
		static LPPackage3Base CommonParse(BYTE* buf, int len)
		{
			T* p = new T();
			memcpy(p, buf, len);
			return p;
		};

		//************************************
		// Method:    package3通用包释放
		// FullName:  Protocol3::CPackage3Mgr::CommonRelease
		// Access:    public static 
		// Returns:   void
		// Qualifier:
		// Parameter: 包体结构体指针
		//************************************
		static void CommonRelease(LPPackage3Base data)
		{
			if (data)
			{
				delete data;
			}
		};

		static BYTE* Package31Unparse(LPPackage3Base data, int* len);
		static LPPackage3Base Package31Parse(BYTE* buf, int len);
		static void Package31Release(LPPackage3Base data);
	};
}