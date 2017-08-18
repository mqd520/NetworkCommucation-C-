#pragma once

#define PRINTFMAXLEN	1024	//MyPrintf字符最大数

namespace NetworkCommunication
{
	//输出信息类型
	enum EInfoType
	{
		Info,//普通信息
		Debug,//调试信息
		Error//错误信息
	};

	void MyPrintf(int type, char* format, ...);

#define PrintfInfo(format,...)	MyPrintf(EInfoType::Info,format,__VA_ARGS__)
#ifdef _DEBUG
#define PrintfDebug(format,...)	MyPrintf(EInfoType::Debug,format,__VA_ARGS__)
#endif // _DEBUG
#define PrintfError(format,...)	MyPrintf(EInfoType::Error,format,__VA_ARGS__)
}