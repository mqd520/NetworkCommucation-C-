#pragma once

#include <minwindef.h>
#include "Def.h"

namespace NetworkCommunication
{
	//������
	enum DemoPackageType
	{
		type1 = 1,
		type2 = 2,
		type3 = 3,
		type4 = 4,//������
		invalid = 0//��Ч
	};


	/////////////////////////////////���嶨��/////////////////////////////////////////
	//����1
	typedef struct tagDemoPackage1 :public PackageBase
	{
		wchar_t* strUsername;
		wchar_t* strPwd;
	}DemoPackage1, *LPDemoPackage1;

	//����2
	typedef	struct tagDemoPackage2 :public PackageBase
	{
		int n1;
		int n2;
	}DemoPackage2, *LPDemoPackage2;

	//����3
	typedef	struct tagDemoPackage3 :public PackageBase
	{
		int n1;
		char str1[10];
		int n2;
		char str2[20];
	}DemoPackage3, *LPDemoPackage3;

	typedef	struct tagKeepAlivePackage :public PackageBase
	{
		BYTE n = 0;
	}KeepAlivePackage, *LPKeepAlivePackage;



	/////////////////////////////////������������/////////////////////////////////////////
	//DemoPackage1������
	class CDemoPackage1Mgr :public CCommonPackageMgr < DemoPackage1 >
	{
		BYTE* Unparse(void* data, int* len);
		void* Parse(BYTE* buf, int len);
		void Release(void* data);
	};
}