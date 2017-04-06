#pragma once

#include <minwindef.h>

#define Protocol3_MainVer	1
#define Protocol3_SecVer	1
#define Protocol3_HeadLen	7

/*	��ͷ����
	1:���汾��
	2:�ΰ汾��
	3:��ͷ����
	4:������(��λ)
	5:������(��λ)
	6:���ݳ���(��λ)
	7:���ݳ���(��λ)
	*/

namespace Protocol3
{
	//��ͷ����
	typedef struct tagPackage3Head
	{
		const BYTE mainVer = Protocol3_MainVer;//���汾��
		const BYTE secVer = Protocol3_SecVer;//�ΰ汾��
		const BYTE headlen = Protocol3_HeadLen;//��ͷ����
		BYTE highPackageType;//������(��λ)
		BYTE lowPackageType;//������(��λ)
		BYTE highDataLen;//���ݳ���(��λ)
		BYTE lowDataLen;//���ݳ���(��λ)
	}Package3Head, *LPPackage3Head;

	//������
	enum Package3Type
	{
		type1 = 1,//Package31
		type2 = 2,//Package32
		type3 = 3,//Package33
		type4 = 4,//KeepAlivePackage
		invalid = 0//��Ч
	};

	//�������
	typedef	struct tagPackage3Base
	{

	}Package3Base, *LPPackage3Base;

	//����1
	typedef struct tagPackage31 :public Package3Base
	{
		wchar_t* strUsername;
		wchar_t* strPwd;
	}Package31, *LPPackage31;

	//����2
	typedef	struct tagPackage32 :public Package3Base
	{
		int n1;
		int n2;
	}Package32, *LPPackage32;

	//����3
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