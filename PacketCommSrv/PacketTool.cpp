#include "stdafx.h"
#include "Include/pck/PacketTool.h"
#include "Include/pck/IGPacket.h"

#define PCR_PacketPointer(CMD, ClassName)		if (cmd == EPacketCmd::CMD){return new ClassName;}

namespace pck
{
	PacketTool::PacketTool()
	{

	}

	bool PacketTool::IsCmdValid(EPacketCmd cmd)
	{
		if (cmd == EPacketCmd::None)
		{
			return false;
		}

		bool b = false;
		for (int i = 0; i < PCR_CmdCount; i++)
		{
			if (cmd == _vecPacketCmds[i])
			{
				b = true;
				break;
			}
		}

		return b;
	}

	Packet* PacketTool::GetPacket(EPacketCmd cmd)
	{
		PCR_PacketPointer(KeepAlive, KeepAlivePacket)
			PCR_PacketPointer(LoginSrvRequest, LoginSrvRequestPacket)
			PCR_PacketPointer(LoginSrvResult, LoginSrvResultPacket)

			return NULL;
	}
}