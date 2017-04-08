#pragma once

#include <minwindef.h>

#define DemoProtocol_MainVer	1
#define DemoProtocol_SecVer		0
#define DemoProtocol_HeadLen	7

/*	包头定义
	1:主版本号
	2:次版本号
	3:包头长度
	4:包类型(高位)
	5:包类型(低位)
	6:数据长度(高位)
	7:数据长度(低位)
	*/

namespace TCPCommunication
{
	//包头定义
	typedef struct tagDemoPackageHead
	{
		const BYTE mainVer = DemoProtocol_MainVer;//主版本号
		const BYTE secVer = DemoProtocol_SecVer;//次版本号
		const BYTE headlen = DemoProtocol_HeadLen;//包头长度
		BYTE highPackageType;//包类型(高位)
		BYTE lowPackageType;//包类型(低位)
		BYTE highDataLen;//数据长度(高位)
		BYTE lowDataLen;//数据长度(低位)
	}DemoPackageHead, *LPDemoPackageHead;

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