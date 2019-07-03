#pragma once
#include "ServiceA.h"
//#include "ServiceB.h"

//using namespace tc;

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
	//ServiceB srvB;		// serviceB

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

	////************************************
	//// Method:    ��ȡServiceB
	////************************************
	//ServiceB& GetSrvB();

	//************************************
	// Method:    ��־�¼�����
	// Parameter: type:	tcp��־����
	// Parameter: log:	��־����
	//************************************
	void WriteLog(ETcpLogType type, string log);
};