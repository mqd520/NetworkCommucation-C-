#include "stdafx.h"
#include "Include/pck/IGPacket.h"
#include "Include/pck/PacketCmd.h"


const int nCmdCount = PCR_CmdCount;
const pck::EPacketCmd _vecPacketCmds[] = {
	pck::EPacketCmd::KeepAlive,
	pck::EPacketCmd::LoginSrvRequest,
	pck::EPacketCmd::LoginSrvResult,

	pck::EPacketCmd::None
};