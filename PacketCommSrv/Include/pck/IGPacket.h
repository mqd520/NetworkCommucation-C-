#pragma once

#include "KeepAlivePacket.h"
#include "LoginSrvRequestPacket.h"
#include "LoginSrvResultPacket.h"


#define PCR_CmdCount			(3 + 1)
extern const pck::EPacketCmd _vecPacketCmds[];		// 命令集合
extern const int nCmdCount;							// 集合个数