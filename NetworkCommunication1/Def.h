#pragma once

#include <minwindef.h>

namespace NetworkCommunication
{
	//包管理接口
	__interface IPackageMgr
	{
		//************************************
		// Method:    反解析包
		// FullName:  IPackageMgr::Unparse
		// Access:    public 
		// Returns:   缓冲区
		// Qualifier:
		// Parameter: 包体结构体指针
		// Parameter: 缓冲区(输出)
		//************************************
		BYTE* Unparse(void* data, int* len);

		//************************************
		// Method:    解析包
		// FullName:  IPackageMgr::Parse
		// Access:    public 
		// Returns:   包体结构体指针
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区大小
		//************************************
		void* Parse(BYTE* buf, int len);

		//************************************
		// Method:    释放包
		// FullName:  IPackageMgr::Release
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 包体结构体指针
		//************************************
		void Release(void* data);
	};

	//包体基类
	typedef	struct tagPackageBase
	{

	}PackageBase, *LPPackageBase;

	template<typename T>
	//通用包管理
	//T: 包体结构体
	class CCommonPackageMgr :public IPackageMgr
	{
	public:
		CCommonPackageMgr(){};
		~CCommonPackageMgr(){};

		virtual BYTE* Unparse(void* data, int* len)
		{
			*len = sizeof(T);
			BYTE* buf = new BYTE[*len];
			memcpy(buf, data, *len);
			return buf;
		};

		virtual void* Parse(BYTE* buf, int len)
		{
			T* p = new T();
			memcpy(p, buf, len);
			return p;
		};

		virtual void Release(void* data)
		{
			if (data)
			{
				delete data;
			}
		};
	};

	class CPackageBase
	{
	public:
		CPackageBase(){};
		~CPackageBase(){};

		int GetCmd(){ return 0; };

		int GetSize(){ return 0; };
	};
}