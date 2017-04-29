#pragma once

#include <minwindef.h>

namespace NetworkCommunication
{
	//������ӿ�
	__interface IPackageMgr
	{
		//************************************
		// Method:    ��������
		// FullName:  IPackageMgr::Unparse
		// Access:    public 
		// Returns:   ������
		// Qualifier:
		// Parameter: ����ṹ��ָ��
		// Parameter: ������(���)
		//************************************
		BYTE* Unparse(void* data, int* len);

		//************************************
		// Method:    ������
		// FullName:  IPackageMgr::Parse
		// Access:    public 
		// Returns:   ����ṹ��ָ��
		// Qualifier:
		// Parameter: ������
		// Parameter: ��������С
		//************************************
		void* Parse(BYTE* buf, int len);

		//************************************
		// Method:    �ͷŰ�
		// FullName:  IPackageMgr::Release
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: ����ṹ��ָ��
		//************************************
		void Release(void* data);
	};

	//�������
	typedef	struct tagPackageBase
	{

	}PackageBase, *LPPackageBase;

	template<typename T>
	//ͨ�ð�����
	//T: ����ṹ��
	class CCommonPackageMgr :public IPackageMgr
	{
	public:
		CCommonPackageMgr(){};
		~CCommonPackageMgr(){};

		virtual BYTE* Unparse(void* data, int* len)
		{
			*len = sizeof(T);
			BYTE* buf = new BYTE[*len];
			memcpy(buf, data, *len);
			return buf;
		};

		virtual void* Parse(BYTE* buf, int len)
		{
			T* p = new T();
			memcpy(p, buf, len);
			return p;
		};

		virtual void Release(void* data)
		{
			if (data)
			{
				delete data;
			}
		};
	};

	class CPackageBase
	{
	public:
		CPackageBase(){};
		~CPackageBase(){};

		int GetCmd(){ return 0; };

		int GetSize(){ return 0; };
	};
}