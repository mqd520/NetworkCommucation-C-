#pragma once

#include "KeepAlivePacket.h"
#include "LoginSrvRequestPacket.h"
#include "LoginSrvResultPacket.h"


#define PCR_CmdCount			(3 + 1)
extern const pck::EPacketCmd _vecPacketCmds[];		// �����
extern const int nCmdCount;							// ���ϸ���