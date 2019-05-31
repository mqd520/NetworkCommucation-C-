#pragma once
#include <vector>
#include <queue>
#include "Include/tc/Def1.h"
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// �ص�������Ϣ
	typedef struct tagLogCallbackInfo
	{
		LPLogCallback lpfn;	// �ص�����ָ��
		void* pParam1;		// ���Ӳ���1
		void* pParam2;		// ���Ӳ���2
	}LogCallbackInfo;

	// ��־��Ϣ
	typedef struct tagLogInfo
	{
		int type;		// ��־����: ELogType
		string log;		// ��־����
	}LogInfo;

	// ��־������
	class LogMgr
	{
	public:
		LogMgr();
		~LogMgr();

	private:
		vector<LogCallbackInfo> vecCallbacks;	// �ص�������Ϣ����
		queue<LogInfo> quLogs;			// ��־����
		CThreadLock lock1;				// �߳���, ���: quLogs

	private:
		friend class LogThread;
		//************************************
		// Method:    ������־
		//************************************
		void ProcessLog();

	public:
		//************************************
		// Method:    ע����־�ص�����
		// Parameter: lpfnCallback:	�ص�����ָ��(�ο�: LPLogCallback)
		// Parameter: pParam1:	���Ӳ���1
		// Parameter: pParam2:	���Ӳ���2
		//************************************
		void RegCallback(LPLogCallback lpfnCallback, void* pParam1 = NULL, void* pParam2 = NULL);

		//************************************
		// Method:    �Ƴ���־�ص�����
		// Parameter: lpfnCallback:	�ص�����ָ��(�ο�: LPLogCallback)
		//************************************
		void RemoveCallback(LPLogCallback lpfnCallback);

		//************************************
		// Method:    �Ƴ���־�ص�����
		//************************************
		void RemoveCallback();

		//************************************
		// Method:    ����һ����־
		// Parameter: type:	��־����(�ο�: ELogType)
		// Parameter: format:	��ʽ���ַ���
		//************************************
		void AddLog(int type, string format, ...);

		//************************************
		// Method:    ��־�Ƿ�Ϊ��
		//************************************
		bool IsEmpty();
	};
}