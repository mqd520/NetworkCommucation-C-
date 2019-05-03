#pragma once

#define PRINTFMAXLEN	1024	//MyPrintf字符最大数

namespace tc
{
	//输出信息类型
	enum EInfoType
	{
		Info,//普通信息
		Debug,//调试信息
		Warning,//警告信息
		Error//错误信息
	};

	void MyPrintf(int type, TCHAR* format, ...);

#define PrintfInfo(format,...)	MyPrintf(EInfoType::Info,format,__VA_ARGS__)
#ifdef _DEBUG
#define PrintfDebug(format,...)	MyPrintf(EInfoType::Debug,format,__VA_ARGS__)
#else
#define PrintfDebug(format,...)
#endif // _DEBUG
#define PrintfWarning(format,...)	MyPrintf(EInfoType::Warning,format,__VA_ARGS__)
#define PrintfError(format,...)	MyPrintf(EInfoType::Error,format,__VA_ARGS__)
}