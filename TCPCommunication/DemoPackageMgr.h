#pragma once

#include "DemoPackage.h"

namespace PackageMgr
{
	class CDemoPackageMgr
	{
	private:
		CDemoPackageMgr(){};
	public:
		~CDemoPackageMgr(){};

		//************************************
		// Method:    package3ͨ�÷�����
		// FullName:  Protocol3::CPackage3Mgr::CommonUnparse
		// Access:    public static 
		// Returns:   ���建����ָ��
		// Qualifier:
		// Parameter: ����ṹ��ָ��
		// Parameter: ���建��������(���)
		//************************************
		template<typename T>
		static BYTE* CommonUnparse(LPDemoPackageBase data, int* len)
		{
			*len = sizeof(T);
			BYTE* buf = new BYTE[*len];
			memcpy(buf, data, *len);
			return buf;
		};

		//************************************
		// Method:    package3ͨ�ý���
		// FullName:  Protocol3::CPackage3Mgr::CommonParse
		// Access:    public static 
		// Returns:   ����ṹ��ָ��
		// Qualifier:
		// Parameter: ���建����ָ��
		// Parameter: ���建��������
		//************************************
		template<typename T>
		static LPDemoPackageBase CommonParse(BYTE* buf, int len)
		{
			T* p = new T();
			memcpy(p, buf, len);
			return p;
		};

		//************************************
		// Method:    package3ͨ�ð��ͷ�
		// FullName:  Protocol3::CPackage3Mgr::CommonRelease
		// Access:    public static 
		// Returns:   void
		// Qualifier:
		// Parameter: ����ṹ��ָ��
		//************************************
		static void CommonRelease(LPDemoPackageBase data)
		{
			if (data)
			{
				delete data;
			}
		};

		static BYTE* DemoPackage1Unparse(LPDemoPackageBase data, int* len);
		static LPDemoPackageBase DemoPackage1Parse(BYTE* buf, int len);
		static void DemoPackage1Release(LPDemoPackageBase data);
	};
}