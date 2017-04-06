#pragma once

#include <minwindef.h>

#define Protocol3_MainVer	1
#define Protocol3_SecVer	1
#define Protocol3_HeadLen	7

/*	包头定义
	1:主版本号
	2:次版本号
	3:包头长度
	4:包类型(高位)
	5:包类型(低位)
	6:数据长度(高位)
	7:数据长度(低位)
	*/

namespace Protocol3
{
	//包头定义
	typedef struct tagPackage3Head
	{
		const BYTE mainVer = Protocol3_MainVer;//主版本号
		const BYTE secVer = Protocol3_SecVer;//次版本号
		const BYTE headlen = Protocol3_HeadLen;//包头长度
		BYTE highPackageType;//包类型(高位)
		BYTE lowPackageType;//包类型(低位)
		BYTE highDataLen;//数据长度(高位)
		BYTE lowDataLen;//数据长度(低位)
	}Package3Head, *LPPackage3Head;

	//包类型
	enum Package3Type
	{
		type1 = 1,//Package31
		type2 = 2,//Package32
		type3 = 3,//Package33
		type4 = 4,//KeepAlivePackage
		invalid = 0//无效
	};

	//包体基类
	typedef	struct tagPackage3Base
	{

	}Package3Base, *LPPackage3Base;

	//包体1
	typedef struct tagPackage31 :public Package3Base
	{
		wchar_t* strUsername;
		wchar_t* strPwd;
	}Package31, *LPPackage31;

	//包体2
	typedef	struct tagPackage32 :public Package3Base
	{
		int n1;
		int n2;
	}Package32, *LPPackage32;

	//包体3
	typedef	struct tagPackage33 :public Package3Base
	{
		int n1;
		char str1[10];
		int n2;
		char str2[20];
	}Package33, *LPPackage33;

	typedef	struct tagKeepAlivePackage :public Package3Base
	{
		BYTE n = 0;
	}KeepAlivePackage, *LPKeepAlivePackage;
}