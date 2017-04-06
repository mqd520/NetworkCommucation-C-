#pragma once

#include "Package3.h"

namespace PackageMgr
{
	//Package3��������ָ��
	typedef BYTE* (*LPPackage3Unparse)(LPPackage3Base data, int* len);
	//Package3������ָ��
	typedef LPPackage3Base(*LPPackage3Parse)(BYTE* buf, int len);
	//Package3���ͷ�ָ��
	typedef void(*LPPackage3Release)(LPPackage3Base data);

	class CPackage3Mgr
	{
	private:
		CPackage3Mgr(){};
	public:
		~CPackage3Mgr(){};

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
		static BYTE* CommonUnparse(LPPackage3Base data, int* len)
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
		static LPPackage3Base CommonParse(BYTE* buf, int len)
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
		static void CommonRelease(LPPackage3Base data)
		{
			if (data)
			{
				delete data;
			}
		};

		static BYTE* Package31Unparse(LPPackage3Base data, int* len);
		static LPPackage3Base Package31Parse(BYTE* buf, int len);
		static void Package31Release(LPPackage3Base data);
	};
}