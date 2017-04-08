#pragma once

#include <vector>
#include "ProtocolTool.h"

using namespace std;
using namespace ProtocolTool;

namespace ProtocolMgr
{
	//Э�����
	template<typename TPackageType, typename TPackageBase>
	//��1��ģ�����:	�����Ͷ���
	//��2��ģ�����:	�������Ͷ���
	class CProtocolMgr
	{
	protected:
		//��������ָ��
		typedef BYTE* (*LPPackageUnparse)(TPackageBase* data, int* len);
		//������ָ��
		typedef TPackageBase* (*LPPackageParse)(BYTE* buf, int len);
		//���ͷ�ָ��
		typedef void(*LPPackageRelease)(TPackageBase* data);

	public:
		//��������Ϣ
		typedef struct tagParserInfo
		{
			LPPackageUnparse	unparse;//��������
			LPPackageParse		parse;//������
			LPPackageRelease	release;//�ͷ���
		}ParserInfo, *LPParserInfo;

	protected:
		//��������Ϣ
		typedef struct tagPackageParseInfo
		{
			TPackageType type;//������
			ParserInfo	parser;//��������Ϣ
		}PackageParseInfo, *LPPackageParseInfo;

	protected:
		int m_nPackageHeadLen;//��ͷ����
		int m_nInvalidPackage;//��Ч��
		int m_nKeepAlive;//������
		vector<PackageParseInfo> m_vecParserList;//������������

	public:
		CProtocolMgr()
		{
			m_nPackageHeadLen = 0;
			m_nInvalidPackage = 0;
			m_nKeepAlive = 0;
		};
		~CProtocolMgr(){};

		//************************************
		// Method:    ��ʼ��
		// FullName:  Protocol3::CProtocol3Handle::Init
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Init(){};

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
		virtual BYTE* PacketFromBuf(TPackageType type, BYTE buf[], int bodyLen, int* packetLen)
		{
			*packetLen = bodyLen;
			return buf;
		};

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
		virtual BYTE* PacketFromData(TPackageType type, TPackageBase* data, int* packetLen)
		{
			CProtocolMgr<TPackageType, TPackageBase>::ParserInfo parser = GetPacketParser(type);
			if (parser.parse)
			{
				int len = 0;
				BYTE* buf = parser.unparse(data, &len);
				if (len > 0)
				{
					BYTE* result = PacketFromBuf(type, buf, len, packetLen);
					delete buf;
					return result;
				}
			}
			return NULL;
		};

		//************************************
		// Method:    �ӻ�������(������ͷ�Ͱ���)������һ������ṹ������
		// FullName:  Protocol3::CProtocol3Handle::Unpacket
		// Access:    public 
		// Returns:   ����ṹ��ָ��
		// Qualifier:
		// Parameter: ������������ָ��
		// Parameter: ����������
		//************************************
		virtual TPackageBase* Unpacket(BYTE buf[], int len)
		{
			TPackageBase* p = NULL;
			if (len > m_nPackageHeadLen)
			{
				TPackageType type = GetPackageType(buf, len);
				CProtocolMgr<TPackageType, TPackageBase>::ParserInfo parser = GetPacketParser(type);
				p = (TPackageBase*)parser.parse(buf + m_nPackageHeadLen, len - m_nPackageHeadLen);
			}
			return p;
		};

		//************************************
		// Method:    ��ȡ��ͷ����
		// FullName:  Protocol3::CProtocol3Handle::GetHeadLen
		// Access:    public 
		// Returns:   ��ͷ����
		// Qualifier:
		//************************************
		virtual int GetHeadLen()
		{
			return m_nPackageHeadLen;
		};

		//************************************
		// Method:    �ӻ������л�ȡ�������ݳ���
		// FullName:  Protocol3::CProtocol3Handle::GetDataLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: ������ָ��
		// Parameter: ����������
		//************************************
		virtual int GetDataLen(BYTE buf[], int len)
		{
			if (len + 1 > m_nPackageHeadLen)
			{
				return MergeByte(buf[6], buf[5]);
			}
			else
			{
				return 0;
			}
		};

		//************************************
		// Method:    �ӻ������л�ȡ������
		// FullName:  Protocol3::CProtocol3Handle::GetPackageType
		// Access:    public 
		// Returns:   ������
		// Qualifier:
		// Parameter: ������ָ��
		// Parameter: ����������
		//************************************
		virtual TPackageType GetPackageType(BYTE buf[], int len)
		{
			if (len + 1 > m_nPackageHeadLen)
			{
				int type = MergeByte(buf[4], buf[3]);
				return TPackageType(type);
			}
			else
			{
				return TPackageType(m_nPackageHeadLen);
			}
		};

		//************************************
		// Method:    ��ȡ��������(���÷������ͷ�ָ��)
		// FullName:  Protocol3::CProtocol3Handle::GetMgr
		// Access:    protected static 
		// Returns:   Protocol3::Package3Mgr*
		// Qualifier:
		// Parameter: ������
		//************************************
		virtual ParserInfo GetPacketParser(TPackageType type)
		{
			CProtocolMgr<TPackageType, TPackageBase>::ParserInfo p = { 0 };
			for (vector<PackageParseInfo>::iterator it = m_vecParserList.begin(); it < m_vecParserList.end(); ++it)
			{
				if (it->type == type)
				{
					p = it->parser;
					break;
				}
			}
			return p;
		};

		//************************************
		// Method:    ��ȡ���建����ָ��
		// FullName:  Protocol3::CProtocol3Handle::GetDataBuf
		// Access:    public static 
		// Returns:   ���建����ָ��
		// Qualifier:
		// Parameter: ��������ָ�� 
		// Parameter: ������������
		//************************************
		virtual BYTE* GetDataBuf(BYTE* buf, int len)
		{
			int datalen = GetDataLen(buf, len);
			int headlen = GetHeadLen();
			BYTE* result = new BYTE[datalen];
			memcpy(result, buf + headlen, datalen);
			return result;
		};

		//************************************
		// Method:    ��ȡ��Ч��
		// FullName:  ProtocolMgr::CProtocolMgr<TPackageType, TPackageBase>::GetInvalidPackage
		// Access:    virtual public 
		// Returns:   int
		// Qualifier:
		//************************************
		virtual int GetInvalidPackage()
		{
			return m_nInvalidPackage;
		};

		//************************************
		// Method:    ��ȡ������
		// FullName:  ProtocolMgr::CProtocolMgr<TPackageType, TPackageBase>::GetKeepAlivePackage
		// Access:    virtual public 
		// Returns:   int
		// Qualifier:
		//************************************
		virtual int GetKeepAlivePackage()
		{
			return m_nKeepAlive;
		};

		//************************************
		// Method:    ��֤������
		// FullName:  ProtocolMgr::CProtocolMgr<TPackageType, TPackageBase>::ValidateKeepAlivePackage
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		// Parameter: ������
		//************************************
		virtual bool ValidateKeepAlivePackage(TPackageBase* data)
		{
			return true;
		}
	};
}