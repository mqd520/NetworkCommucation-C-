#pragma once

#include "DemoPackage.h"

namespace PackageMgr
{
	class CDemoPackageMgr
	{
	private:
		CDemoPackageMgr(){};
	public:
		~CDemoPackageMgr(){};

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
		static BYTE* CommonUnparse(LPDemoPackageBase data, int* len)
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
		static LPDemoPackageBase CommonParse(BYTE* buf, int len)
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
		static void CommonRelease(LPDemoPackageBase data)
		{
			if (data)
			{
				delete data;
			}
		};

		static BYTE* DemoPackage1Unparse(LPDemoPackageBase data, int* len);
		static LPDemoPackageBase DemoPackage1Parse(BYTE* buf, int len);
		static void DemoPackage1Release(LPDemoPackageBase data);
	};
}