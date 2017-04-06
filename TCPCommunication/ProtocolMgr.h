#pragma once

#include <vector>
#include "Package3.h"
#include "Package3Mgr.h"

using namespace std;

namespace Protocol3
{
	//��������Ϣ
	typedef struct tagParserInfo
	{
		LPPackage3Unparse	unparse;//��������
		LPPackage3Parse		parse;//������
		LPPackage3Release	release;//�ͷ���
	}ParserInfo, *LPParserInfo;

	//Э�����
	class CProtocolMgr
	{
	public:
		CProtocolMgr(){};
		~CProtocolMgr(){};

		//************************************
		// Method:    ��ʼ��
		// FullName:  Protocol3::CProtocol3Handle::Init
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void Init();

		//************************************
		// Method:    ���(���÷��ͷŻ�����ָ��)
		// FullName:  Protocol3::CProtocol3Handle::Packet
		// Access:    public 
		// Returns:   ��������ָ��
		// Qualifier:
		// Parameter: ������
		// Parameter: �������ݻ�����ָ��
		// Parameter: �������ݻ���������
		// Parameter: ������������(���)
		//************************************
		BYTE* Packet(Package3Type type, BYTE buf[], int bodyLen, int* packetLen);

		//************************************
		// Method:    ���(���÷��ͷŻ�����ָ��)
		// FullName:  Protocol3::CProtocol3Handle::Packet
		// Access:    public static 
		// Returns:   ��������ָ��
		// Qualifier:
		// Parameter: ������
		// Parameter: ����ṹ��ָ��
		// Parameter: ������������(���)
		//************************************
		BYTE* Packet(Package3Type type, LPPackage3Base data, int* packetLen);

		//************************************
		// Method:    ��һ���������������н���һ����������
		// FullName:  Protocol3::CProtocol3Handle::Unpacket
		// Access:    public 
		// Returns:   ����ṹ��ָ��
		// Qualifier:
		// Parameter: ������������ָ��
		// Parameter: ����������
		//************************************
		void* Unpacket(BYTE buf[], int len);

		//************************************
		// Method:    ��ȡ��ͷ����
		// FullName:  Protocol3::CProtocol3Handle::GetHeadLen
		// Access:    public 
		// Returns:   ��ͷ����
		// Qualifier:
		//************************************
		int GetHeadLen();

		//************************************
		// Method:    �ӻ������л�ȡ�������ݳ���
		// FullName:  Protocol3::CProtocol3Handle::GetDataLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: ������ָ��
		// Parameter: ����������
		//************************************
		int GetDataLen(BYTE buf[], int len);

		//************************************
		// Method:    �ӻ������л�ȡ������
		// FullName:  Protocol3::CProtocol3Handle::GetPackageType
		// Access:    public 
		// Returns:   ������
		// Qualifier:
		// Parameter: ������ָ��
		// Parameter: ����������
		//************************************
		Package3Type GetPackageType(BYTE buf[], int len);

		//************************************
		// Method:    ��ȡ��������(���÷������ͷ�ָ��)
		// FullName:  Protocol3::CProtocol3Handle::GetMgr
		// Access:    protected static 
		// Returns:   Protocol3::Package3Mgr*
		// Qualifier:
		// Parameter: ������
		//************************************
		ParserInfo GetPacketParser(Package3Type type);

		//************************************
		// Method:    ��ȡ���建����ָ��
		// FullName:  Protocol3::CProtocol3Handle::GetDataBuf
		// Access:    public static 
		// Returns:   ���建����ָ��
		// Qualifier:
		// Parameter: ��������ָ�� 
		// Parameter: ������������
		//************************************
		BYTE* GetDataBuf(BYTE* buf, int len);

	protected:
		//Package3��������Ϣ
		typedef struct tagPackage3ParseInfo
		{
			Package3Type type;//������
			ParserInfo	parser;//��������Ϣ
		}Package3ParseInfo, *LPPackage3ParseInfo;

		vector<Package3ParseInfo> m_vecParserList;//������������
	};
}