#pragma once

#include "Package3.h"

namespace Protocol3
{
	class CProtocol3Handle
	{
	public:
		CProtocol3Handle();
		~CProtocol3Handle();

		//************************************
		// Method:    ���,�������ͷ��ڴ�
		// FullName:  Protocol3::CProtocol3Handle::Packet
		// Access:    public 
		// Returns:   BYTE*
		// Qualifier:
		// Parameter: ��������
		// Parameter: �������ݻ�����ָ��
		// Parameter: ����������
		//************************************
		BYTE* Packet(Package3Type type, BYTE buf[], int len);

		void* Unpacket(BYTE buf[], int len, Package3Type type);

		//************************************
		// Method:    ��ȡ��ͷ����
		// FullName:  Protocol3::CProtocol3Handle::GetHeadLen
		// Access:    public 
		// Returns:   ��ͷ����
		// Qualifier:
		//************************************
		int GetHeadLen();

		//************************************
		// Method:    ��һ���������������л�ȡ�������ݳ���
		// FullName:  Protocol3::CProtocol3Handle::GetDataLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: һ�����������ֽ�����
		// Parameter: �ֽ����鳤��
		//************************************
		int GetDataLen(BYTE buf[], int len);

		//************************************
		// Method:    ��һ���������������л�ȡ������
		// FullName:  Protocol3::CProtocol3Handle::GetPackageType
		// Access:    public 
		// Returns:   ������
		// Qualifier:
		// Parameter: һ�����������ֽ�����
		// Parameter: �ֽ����鳤��
		//************************************
		Package3Type GetPackageType(BYTE buf[], int len);

	protected:
		//************************************
		// Method:    ��������,���������ڴ�İ������ݽṹ
		// FullName:  Protocol3::CProtocol3Handle::Parse
		// Access:    protected 
		// Returns:   �������ݽṹָ��(��Ҫ�������ͷ�)
		// Qualifier:
		// Parameter: һ�����������ֽ�����
		// Parameter: �ֽ����鳤��
		//************************************
		template<typename T>
		T* Parse(BYTE buf[], int len);
	};
}