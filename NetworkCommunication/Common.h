#pragma once

#define PRINTFMAXLEN	1024	//MyPrintf�ַ������

namespace NetworkCommunication
{
	//�����Ϣ����
	enum EInfoType
	{
		Info,//��ͨ��Ϣ
		Debug,//������Ϣ
		Error//������Ϣ
	};

	void MyPrintf(int type, char* format, ...);

#define PrintfInfo(format,...)	MyPrintf(EInfoType::Info,format,__VA_ARGS__)
#ifdef _DEBUG
#define PrintfDebug(format,...)	MyPrintf(EInfoType::Debug,format,__VA_ARGS__)
#endif // _DEBUG
#define PrintfError(format,...)	MyPrintf(EInfoType::Error,format,__VA_ARGS__)
}