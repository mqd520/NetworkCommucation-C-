#pragma once

namespace lib1
{
	// ������
	enum class EPacketCmd : int
	{
		KeepAlive = 1,					// ������
		LoginSrvRequest = 8,			// ��¼����������
		LoginSrvResult = 9,				// ��¼����˽����


		PlayerRequestLogin,				// ��������½��
		PlayerLoginResult,				// ��ҵ�½�����


		None							// None
	};
}