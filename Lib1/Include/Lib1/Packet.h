#pragma once
#include "tc/PacketBase.h"

using namespace tc;

namespace lib1
{
	// ������
	class KeepAlivePck : public PacketBase
	{
	public:
		KeepAlivePck(BYTE* pBuf = NULL, int len = 0, bool bigEndian = true);
		~KeepAlivePck();

	public:
		BYTE cbKeepAlive;		// n1, 1���ֽ�

	public:
		//************************************
		// Method:    ��ȡ������(������ͷ)
		//************************************
		virtual int GetLen();

		//************************************
		// Method:    �����ж�ȡ���ݵ�����
		// Parameter: ns:	ֻ������������
		//************************************
		virtual void Read(CNetworkStreamRead& ns) override;

		//************************************
		// Method:    ������д������
		// Parameter: ns:	ֻд����������
		//************************************
		virtual void Write(CNetworkStreamWrite& ns) override;
	};


	// ��¼����������
	class LoginSrRequestPck : public PacketBase
	{
	public:
		LoginSrRequestPck(BYTE* pBuf = NULL, int len = 0, bool bigEndian = true);
		~LoginSrRequestPck();

	public:
		BYTE		cbCurrentServerType;	// ��ǰ��������, 1���ֽ�
		BYTE		cbRequestServerID;		// ����ķ�����id, 1���ֽ�
		BYTE		cbKeepAlive;			// ����ֵ, 1���ֽ�
		INT32		nVersion;				// �汾, 4���ֽ�
		string		strGuid;				// GUID

	public:
		//************************************
		// Method:    ��ȡ������(������ͷ)
		//************************************
		virtual int GetLen() override;

		//************************************
		// Method:    �����ж�ȡ���ݵ�����
		// Parameter: ns:	ֻ������������
		//************************************
		virtual void Read(CNetworkStreamRead& ns) override;

		//************************************
		// Method:    ������д������
		// Parameter: ns:	ֻд����������
		//************************************
		virtual void Write(CNetworkStreamWrite& ns) override;
	};



	// ��¼����˽����
	class LoginSrResultPck : public PacketBase
	{
	public:
		LoginSrResultPck(BYTE* pBuf = NULL, int len = 0, bool bigEndian = true);
		~LoginSrResultPck();

	public:
		BYTE		cbVerifyCode;	// code, 1���ֽ�
		INT32		nServerID;		// server id, 4���ֽ�

	public:
		//************************************
		// Method:    ��ȡ������(������ͷ)
		//************************************
		virtual int GetLen() override;

		//************************************
		// Method:    �����ж�ȡ���ݵ�����
		// Parameter: ns:	ֻ������������
		//************************************
		virtual void Read(CNetworkStreamRead& ns) override;

		//************************************
		// Method:    ������д������
		// Parameter: ns:	ֻд����������
		//************************************
		virtual void Write(CNetworkStreamWrite& ns) override;
	};
}