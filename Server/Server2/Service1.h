#pragma once
#include "ServiceA.h"

#include "tc/Def.h"
using namespace tc;


// Service1
class Service1
{
public:
	Service1();
	~Service1();

protected:
	ServiceA srvA;		// serviceA

public:
	//************************************
	// Method:    初始化
	//************************************
	void Init();

	//************************************
	// Method:    退出
	//************************************
	void Exit();

	//************************************
	// Method:    获取ServiceA
	//************************************
	ServiceA& GetSrvA();

	//************************************
	// Method:    日志事件处理
	// Parameter: type:	tcp日志类型
	// Parameter: log:	日志内容
	//************************************
	void WriteLog(ETcpLogType type, string log);
};