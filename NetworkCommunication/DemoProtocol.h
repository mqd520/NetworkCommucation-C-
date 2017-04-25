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

		Login = 511,//��¼�����
		LoginReply = 512//��¼Ӧ���
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

	//��¼�����
	typedef struct tagLoginPackage :public PackageBase
	{
		wchar_t strUsername[15];//�û���
		wchar_t strPwd[15];//����
	}LoginPackage, *LPLoginPackage;

	//��¼Ӧ���
	typedef	struct tagLoginReplyPackage :public PackageBase
	{
		bool b;//��¼�Ƿ�ɹ�
		wchar_t msg[30];//������Ϣ
	}LoginReplyPackage, *LPLoginReplyPackage;


	/////////////////////////////////��������/////////////////////////////////////////
	//Э���¼������
	class CProtocolLoginPackageMgr :public CCommonPackageMgr < ProtocolLoginPackage >
	{
		BYTE* Unparse(void* data, int* len);
		void* Parse(BYTE* buf, int len);
		void Release(void* data);
	};
}