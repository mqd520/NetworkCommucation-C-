#pragma once

#include <string>

using namespace std;

//************************************
// Method:    异常回调函数指针
// Parameter: pParam1:	附加参数1
// Parameter: pParam1:	附加参数2
//************************************
typedef void(*LPExceptionCallback)(void* pParam1, void* pParam2);

// 异常处理类
class ExceptionHandler
{
private:
	ExceptionHandler();
	~ExceptionHandler();

public:
	static void Init();

	//************************************
	// Method:    设置文件名
	// Parameter: strFilename:	文件名
	//************************************
	static void SetFileName(string strFilename);

	//************************************
	// Method:    注册异常处理回调函数
	// Parameter: lpfnCallback:	回调函数指针
	// Parameter: pParam1:	附加参数1
	// Parameter: pParam1:	附加参数2
	//************************************
	static void RegExceptionCallback(LPExceptionCallback lpfnCallback, void* pParam1 = NULL, void* pParam2 = NULL);
};