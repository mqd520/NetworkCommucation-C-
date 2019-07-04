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
	// Method:    ��ʼ��
	//************************************
	void Init();

	//************************************
	// Method:    �˳�
	//************************************
	void Exit();

	//************************************
	// Method:    ��ȡServiceA
	//************************************
	ServiceA& GetSrvA();

	//************************************
	// Method:    ��־�¼�����
	// Parameter: type:	tcp��־����
	// Parameter: log:	��־����
	//************************************
	void WriteLog(ETcpLogType type, string log);
};