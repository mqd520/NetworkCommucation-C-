#pragma once

#include <string>
#include <fstream>
#include <queue>
#include "LogThread.h"

using namespace std;

// ��־����
enum class ELogType : int
{
	Info,			// ��Ϣ
	Warn,			// ����
	Debug,			// ����
	Error,			// ����
	Fatal,			// ���ش���

	Other = 99
};

// ��־������
class LogSrv
{
private:
	LogSrv();

public:
	~LogSrv();

private:
	static LogSrv instance;		// log srv
	static LogThread logThread;	// log thread

private:
	queue<string>	queueLog;	// log queue

private:
	void WriteLog(string& log);	// д����־

public:
	static void Init();

	static void Exit();

	static LogSrv* GetInstance();

	void Add(string log, ELogType type = ELogType::Info);

	bool IsEmpty();

	void Clear();

	void ProcessLog();
};