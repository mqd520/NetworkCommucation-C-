#pragma once

#include <minwindef.h>
#include "Def.h"

namespace NetworkCommunication
{
	//������
	enum DemoPackageType
	{
		KeepAlive = 1,//������
		ProtocolLogin = 8,//Э���¼
		ProtocolLoginReply = 9,//Э���¼Ӧ��

		Other = 100
	};


	/////////////////////////////////���嶨��/////////////////////////////////////////
	//������
	typedef	struct tagKeepAlivePackage :public PackageBase
	{
		BYTE n = 0;
	}KeepAlivePackage, *LPKeepAlivePackage;

	//Э���¼��
	typedef	struct tagProtocolLoginPackage :public PackageBase
	{
		BYTE cbCurrentServerType;
		BYTE cbRequestServerID;
		BYTE cbKeepAlive;
		INT32 nVersion;
		char* strGuid;
	}ProtocolLoginPackage, *LPProtocolLoginPackage;

	//Э���¼Ӧ���
	typedef	struct tagProtocolLoginReplyPackage :public PackageBase
	{
		BYTE cbVerifyCode;//��֤��
		int nServerID;//������ID
	}ProtocolLoginReplyPackage, *LPProtocolLoginReplyPackage;


	/////////////////////////////////��������/////////////////////////////////////////
	//Э���¼������
	class CProtocolLoginPackageMgr :public CCommonPackageMgr < ProtocolLoginPackage >
	{
		BYTE* Unparse(void* data, int* len);
		void* Parse(BYTE* buf, int len);
		void Release(void* data);
	};

	//Э���¼Ӧ�������
	class CProtocolLoginReplyPackageMgr :public CCommonPackageMgr < ProtocolLoginReplyPackage >
	{
		BYTE* Unparse(void* data, int* len);
		void* Parse(BYTE* buf, int len);
		void Release(void* data);
	};
}