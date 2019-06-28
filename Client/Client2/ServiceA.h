#pragma once
#include <string>
#include "lib1/LibClient.h"

using namespace std;
using namespace lib1;

class Service1;

// 服务A
class ServiceA : public LibClient
{
public:
	ServiceA(Service1* pSrv1 = NULL, string ip = "", int port = 0);
	~ServiceA();

protected:
	Service1* pSrv1;

protected:
	//************************************
	// Method:    日志事件处理
	// Parameter: type:	tcp日志类型
	// Parameter: log:	日志内容
	//************************************
	virtual void OnLog(ETcpLogType type, string log) override;

	//************************************
	// Method:    处理业务包事件处理程序
	// Parameter: data:	包数据
	//************************************
	virtual void OnProcessBusinessPck(PacketData& data) override;

public:
	void SetService(Service1* pSrv1);
};