#pragma once

#define Lib1_PacketMask						(32616)					// ��ͷmask
#define Lib1_PacketHeadLen					(7)						// ��ͷ����
#define Lib1_ConnectPwd						("abcdefg")				// ������������
#define LIB1_MAXSENDBULEN					(1024)					// Ĭ������ͻ���������
#define Lib1_Version						(0x0007)				// �汾
#define Lib1_keepAlive						(0x0001)				// keepalive
#define Lib1_ServerId						(0x0001)				// serverId
#define Lib1_MaxPacketLen					(0x8096)				// ���建�����ֽ���󳤶�
#define Lib1_KeepAliveTimespan1				(10 * 1000)				// ��ʧ������ʱ����
#define Lib1_KeepAliveTimespan2				(2 * 1000)				// ����������ʱ����
#define Lib1_VertifyCode					(66)					// ��֤��
#define Lib1_MaxMissCount					(3)						// �������ʧ�������Ĵ���(�����󽫹ر�����)
#define Lib1_PwdTimeout						(3 * 1000)				// ����˽�������ĳ�ʱʱ��
#define Lib1_LoginRequestTimeout			(3 * 1000)				// ����˽��ܵ�¼��������ĳ�ʱʱ��


namespace lib1
{
	// ��������
	enum class ELibSrvType : int
	{
		Client,
		Server
	};
}