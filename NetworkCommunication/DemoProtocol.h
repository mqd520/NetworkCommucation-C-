#pragma once

#include <minwindef.h>
#include "Def.h"

namespace NetworkCommunication
{
	//包类型
	enum DemoPackageType
	{
		type1 = 1,
		type2 = 2,
		type3 = 3,
		type4 = 4,//心跳包
		invalid = 0//无效
	};


	/////////////////////////////////包体定义/////////////////////////////////////////
	//包体1
	typedef struct tagDemoPackage1 :public PackageBase
	{
		wchar_t* strUsername;
		wchar_t* strPwd;
	}DemoPackage1, *LPDemoPackage1;

	//包体2
	typedef	struct tagDemoPackage2 :public PackageBase
	{
		int n1;
		int n2;
	}DemoPackage2, *LPDemoPackage2;

	//包体3
	typedef	struct tagDemoPackage3 :public PackageBase
	{
		int n1;
		char str1[10];
		int n2;
		char str2[20];
	}DemoPackage3, *LPDemoPackage3;

	typedef	struct tagKeepAlivePackage :public PackageBase
	{
		BYTE n = 0;
	}KeepAlivePackage, *LPKeepAlivePackage;



	/////////////////////////////////包管理器定义/////////////////////////////////////////
	//DemoPackage1包管理
	class CDemoPackage1Mgr :public CCommonPackageMgr < DemoPackage1 >
	{
		BYTE* Unparse(void* data, int* len);
		void* Parse(BYTE* buf, int len);
		void Release(void* data);
	};
}