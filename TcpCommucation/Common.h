#pragma once

#define PRINTFMAXLEN	1024	//MyPrintf�ַ������

namespace tc
{
	//�����Ϣ����
	enum EInfoType
	{
		Info,//��ͨ��Ϣ
		Debug,//������Ϣ
		Warning,//������Ϣ
		Error//������Ϣ
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