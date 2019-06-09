#pragma once

#include <string>

using namespace std;

//************************************
// Method:    �쳣�ص�����ָ��
// Parameter: pParam1:	���Ӳ���1
// Parameter: pParam1:	���Ӳ���2
//************************************
typedef void(*LPExceptionCallback)(void* pParam1, void* pParam2);

// �쳣������
class ExceptionHandler
{
private:
	ExceptionHandler();
	~ExceptionHandler();

public:
	static void Init();

	//************************************
	// Method:    �����ļ���
	// Parameter: strFilename:	�ļ���
	//************************************
	static void SetFileName(string strFilename);

	//************************************
	// Method:    ע���쳣�����ص�����
	// Parameter: lpfnCallback:	�ص�����ָ��
	// Parameter: pParam1:	���Ӳ���1
	// Parameter: pParam1:	���Ӳ���2
	//************************************
	static void RegExceptionCallback(LPExceptionCallback lpfnCallback, void* pParam1 = NULL, void* pParam2 = NULL);
};