#pragma once

#include <minwindef.h>

#define DemoProtocol_MainVer	1
#define DemoProtocol_SecVer		0
#define DemoProtocol_HeadLen	7

/*	��ͷ����
	1:���汾��
	2:�ΰ汾��
	3:��ͷ����
	4:������(��λ)
	5:������(��λ)
	6:���ݳ���(��λ)
	7:���ݳ���(��λ)
	*/

namespace TCPCommunication
{
	//��ͷ����
	typedef struct tagDemoPackageHead
	{
		const BYTE mainVer = DemoProtocol_MainVer;//���汾��
		const BYTE secVer = DemoProtocol_SecVer;//�ΰ汾��
		const BYTE headlen = DemoProtocol_HeadLen;//��ͷ����
		BYTE highPackageType;//������(��λ)
		BYTE lowPackageType;//������(��λ)
		BYTE highDataLen;//���ݳ���(��λ)
		BYTE lowDataLen;//���ݳ���(��λ)
	}DemoPackageHead, *LPDemoPackageHead;

	//������
	enum DemoPackageType
	{
		type1 = 1,
		type2 = 2,
		type3 = 3,
		type4 = 4,//������
		invalid = 0//��Ч
	};

	//�������
	typedef	struct tagDemoPackageBase
	{

	}DemoPackageBase, *LPDemoPackageBase;

	//����1
	typedef struct tagDemoPackage1 :public DemoPackageBase
	{
		wchar_t* strUsername;
		wchar_t* strPwd;
	}DemoPackage1, *LPDemoPackage1;

	//����2
	typedef	struct tagDemoPackage2 :public DemoPackageBase
	{
		int n1;
		int n2;
	}DemoPackage2, *LPDemoPackage2;

	//����3
	typedef	struct tagDemoPackage3 :public DemoPackageBase
	{
		int n1;
		char str1[10];
		int n2;
		char str2[20];
	}DemoPackage3, *LPDemoPackage3;

	typedef	struct tagKeepAlivePackage :public DemoPackageBase
	{
		BYTE n = 0;
	}KeepAlivePackage, *LPKeepAlivePackage;
}