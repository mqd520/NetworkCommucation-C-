#pragma once

#include "DemoPackage.h"

namespace TCPCommunication
{
	template<typename T>
	//DemoPackage管理基类
	class CDemoPackageMgr :public IPackageMgr
	{
	public:
		CDemoPackageMgr(){};
		~CDemoPackageMgr(){};

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

	//DemoPackage1包管理
	class CDemoPackage1Mgr :public CDemoPackageMgr < DemoPackage1 >
	{
		BYTE* Unparse(void* data, int* len);
		void* Parse(BYTE* buf, int len);
		void Release(void* data);
	};
}