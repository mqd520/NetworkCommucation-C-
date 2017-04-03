#pragma once

#define MainVer	1	//主版本号
#define SecVer	0	//次版本号
#define HeadLen	7	//包头长度

/*
	1:主版本号
	2:次版本号
	3:包头长度
	4:包类型(高位)
	5:包类型(低位)
	6:数据长度(高位)
	7:数据长度(低位)
	n:数据
	*/

namespace Protocol1
{
	//包定义
	typedef struct tagPackage1
	{
		const BYTE mainVer = MainVer;//主版本号
		const BYTE secVer = SecVer;//次版本号
		const BYTE headlen = HeadLen;//包头长度
		BYTE highPackType;//包类型(高位)
		BYTE lowPackType;//包类型(低位)
		BYTE highDataLen;//数据长度(高位)
		BYTE lowDataLen;//数据长度(低位)
		BYTE* data;//数据
	}Package1, *LPPackage1;

	//包类型
	enum Package1Type
	{
		type1 = 1,//Data1
		type2 = 2//Data2
	};

	//PackageCmd1::cmd1数据结构
	typedef	struct tagData1
	{
		wchar_t strUsername;//用户名
		wchar_t strPwd;//密码
	}Data1, *LPData1;

	//PackageCmd1::cmd2数据结构
	typedef	struct tagData2
	{
		bool bSuccess;//成功与否
		wchar_t* msg;//错误信息
	}Data2, *LPData2;
}