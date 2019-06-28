#pragma once
#include <string>
#include "Lib1/LibServer.h"

using namespace lib1;

class Service1;

// ����B
class ServiceB : public LibServer
{
public:
	ServiceB(Service1* pSrv1 = NULL, string ip = "", int port = 0);
	~ServiceB();

protected:
	Service1* pSrv1;

protected:
	//************************************
	// Method:    ��־�¼�����
	// Parameter: type:	tcp��־����
	// Parameter: log:	��־����
	//************************************
	virtual void OnLog(ETcpLogType type, string log) override;

	//************************************
	// Method:    ����ҵ����¼��������
	// Parameter: data:	������
	//************************************
	virtual void OnProcessBusinessPck(PacketData& data) override;

public:
	void SetService(Service1* pSrv1);
};