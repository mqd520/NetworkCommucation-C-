#pragma once

#include <vector>
#include "PacketBase.h"
#include "PacketHeadBase.h"

using namespace std;
using namespace NetworkCommunication;

namespace DemoProtocolMgr
{
	/////////////////////////////////�������/////////////////////////////////////////
	class DemoPacketCmd
	{
	public:
		enum
		{
			KeepAlive = 1,//������
			ServiceLogin = 8,//�����¼
			ServiceLoginReply = 9,//�����¼Ӧ��

			DealerLogin = 511,//�ɹٵ�½
			DealerLoginResult = 512//�ɹٵ�½
		};
	};

	/////////////////////////////////��ͷ����/////////////////////////////////////////
#define DemoPacketHead_Mask 32616		//��ͷ���
#define DemoPacketHead_Len (2+2+2+1)	//��ͷ����
	class DemoPacketHead :public PacketHeadBase
	{
	public:
		DemoPacketHead();
		~DemoPacketHead();

	protected:
		short nMask;//��ͷ���
		short nCmd;//������
		short nLen;//��ͷ+�����ܳ���
		BYTE cbCode;//��֤��

	public:
		int GetHeadLen();
		int GetPacketLen();
		int GetTotalLen();
		int GetCmd();
		BYTE* Read(int cmd, int len);
		void Write(BYTE* buf, int len);
		bool IsValid();
	};

	/////////////////////////////////���嶨��/////////////////////////////////////////
#define Packet_Declare_Begin(classname)\
	class classname:public PacketBase{\
	public:\
		classname();\
		~classname();\
		\
	public:\

#define Packet_Declare_End\
	public:\
		int GetCmd();\
		BYTE* Read(int* len);\
		void Write(BYTE* buf, int len);\
		void Release();};

	//������
	Packet_Declare_Begin(KeepAlivePack)
		BYTE n = 0;
	Packet_Declare_End

		//�����½��
		Packet_Declare_Begin(ServiceLoginPack)
		BYTE cbCurrentServerType;
	BYTE cbRequestServerID;
	BYTE cbKeepAlive;
	int nVersion;
	char* strGuid = NULL;
	Packet_Declare_End

		//�����½Ӧ���
		Packet_Declare_Begin(ServiceLoginReplyPack)
		BYTE cbVerifyCode;//��֤��
	int nServerID;//������ID
	Packet_Declare_End

		//�ɹٵ�¼��
		Packet_Declare_Begin(DealerLoginPack)
		wchar_t* strName;//�û���
	wchar_t* strPwd;//����
	int nTableID;//̨��ID
	vector<wchar_t*> vecMac;//mac��ַ����
	INT64 DealerSSID;//ssid
	Packet_Declare_End

		//�ɹٵ�¼�����
		Packet_Declare_Begin(DealerLoginResultPack)
	int nTableID;//̨��ID
	int nResult;//��½���
	int nReloginCode;//���µ�½��
	Packet_Declare_End
}