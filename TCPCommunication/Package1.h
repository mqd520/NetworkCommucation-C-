#pragma once

#define MainVer	1	//���汾��
#define SecVer	0	//�ΰ汾��
#define HeadLen	7	//��ͷ����

/*
	1:���汾��
	2:�ΰ汾��
	3:��ͷ����
	4:������(��λ)
	5:������(��λ)
	6:���ݳ���(��λ)
	7:���ݳ���(��λ)
	n:����
	*/

namespace Protocol1
{
	//������
	typedef struct tagPackage1
	{
		const BYTE mainVer = MainVer;//���汾��
		const BYTE secVer = SecVer;//�ΰ汾��
		const BYTE headlen = HeadLen;//��ͷ����
		BYTE highPackType;//������(��λ)
		BYTE lowPackType;//������(��λ)
		BYTE highDataLen;//���ݳ���(��λ)
		BYTE lowDataLen;//���ݳ���(��λ)
		BYTE* data;//����
	}Package1, *LPPackage1;

	//������
	enum Package1Type
	{
		type1 = 1,//Data1
		type2 = 2//Data2
	};

	//PackageCmd1::cmd1���ݽṹ
	typedef	struct tagData1
	{
		wchar_t strUsername;//�û���
		wchar_t strPwd;//����
	}Data1, *LPData1;

	//PackageCmd1::cmd2���ݽṹ
	typedef	struct tagData2
	{
		bool bSuccess;//�ɹ����
		wchar_t* msg;//������Ϣ
	}Data2, *LPData2;
}