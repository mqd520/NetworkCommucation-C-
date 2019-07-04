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
	// Method:    Ԥ�������
	// Parameter: data:	������
	//************************************
	virtual void PreProcessPck(PacketData& data) override;

	//************************************
	// Method:    ������¼��������
	// Parameter: data:	������
	//************************************
	virtual void OnProcessPck(PacketData& data) override;
};