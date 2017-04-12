#pragma once

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