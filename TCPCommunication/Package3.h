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
		invalid = 0,//��Ч
		type1 = 1,//Package31
		type2 = 2//Package32
	};

	//��½�����
	typedef struct tagPackage31
	{
		wchar_t* strUsername;
		wchar_t* strPwd;
	}Package31, *LPPackage31;

	//��½Ӧ���
	typedef struct tagPackage32
	{
		bool bSuccess;//�Ƿ�ɹ���½
		wchar_t* strMsg;//������Ϣ
	}Package32, *LPPackage32;
}