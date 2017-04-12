#pragma once

#include <minwindef.h>

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

	//包体基类
	typedef	struct tagDemoPackageBase
	{

	}DemoPackageBase, *LPDemoPackageBase;

	//包体1
	typedef struct tagDemoPackage1 :public DemoPackageBase
	{
		wchar_t* strUsername;
		wchar_t* strPwd;
	}DemoPackage1, *LPDemoPackage1;

	//包体2
	typedef	struct tagDemoPackage2 :public DemoPackageBase
	{
		int n1;
		int n2;
	}DemoPackage2, *LPDemoPackage2;

	//包体3
	typedef	struct tagDemoPackage3 :public DemoPackageBase
	{
		int n1;
		char str1[10];
		int n2;
		char str2[20];
	}DemoPackage3, *LPDemoPackage3;

	typedef	struct tagKeepAlivePackage :public DemoPackageBase
	{
		BYTE n = 0;
	}KeepAlivePackage, *LPKeepAlivePackage;
}