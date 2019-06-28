#pragma once

#include <string>
#include <fstream>
#include <queue>
#include "LogThread.h"

using namespace std;

// 日志类型
enum class ELogType : int
{
	Info,			// 信息
	Warn,			// 警告
	Debug,			// 调试
	Error,			// 错误
	Fatal,			// 严重错误

	Other = 99
};

// 日志服务类
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
	void WriteLog(string& log);	// 写入日志

public:
	static void Init();

	static void Exit();

	static LogSrv* GetInstance();

	void Add(string log, ELogType type = ELogType::Info);

	bool IsEmpty();

	void Clear();

	void ProcessLog();
};