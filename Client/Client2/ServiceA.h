#pragma once
#include <string>
#include "lib1/LibClient.h"

using namespace std;
using namespace lib1;

class Service1;

// ����A
class ServiceA : public LibClient
{
public:
	ServiceA(Service1* pSrv1 = NULL, string ip = "", int port = 0);
	~ServiceA();

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