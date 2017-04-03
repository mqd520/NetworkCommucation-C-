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
		invalid = 0,//无效
		type1 = 1,//Package31
		type2 = 2//Package32
	};

	//登陆请求包
	typedef struct tagPackage31
	{
		wchar_t* strUsername;
		wchar_t* strPwd;
	}Package31, *LPPackage31;

	//登陆应答包
	typedef struct tagPackage32
	{
		bool bSuccess;//是否成功登陆
		wchar_t* strMsg;//错误信息
	}Package32, *LPPackage32;
}