#pragma once

namespace pck
{
	// packet cmd
	enum class EPacketCmd : int
	{
		KeepAlive = 1,					// ������
		LoginSrvRequest = 8,			// ��¼����������
		LoginSrvResult = 9,				// ��¼����˽����


		None
	};
}