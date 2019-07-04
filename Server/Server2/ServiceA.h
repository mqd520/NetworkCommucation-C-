#pragma once

#include "pck/IGPacketSrvServer.h"
using namespace pck;

// service A
class ServiceA : public IGPacketSrvServer
{
public:
	ServiceA(string ip = "", int port = 0);

protected:
	//************************************
	// Method:    预处理处理包
	// Parameter: data:	包数据
	//************************************
	virtual void PreProcessPck(PacketData& data) override;

	//************************************
	// Method:    处理包事件处理程序
	// Parameter: data:	包数据
	//************************************
	virtual void OnProcessPck(PacketData& data) override;
};