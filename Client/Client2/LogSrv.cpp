#include "stdafx.h"
#include "LogSrv.h"
#include <time.h>

string GetProgramDir()
{
	char exeFullPath[MAX_PATH] = { 0 };

	GetModuleFileNameA(NULL, exeFullPath, MAX_PATH);
	string strPath = exeFullPath;
	int pos = strPath.find_last_of('\\', strPath.length());
	return strPath.substr(0, pos + 1);
}

LogSrv			LogSrv::instance;
LogThread		LogSrv::logThread;

LogSrv::LogSrv()
{

}

LogSrv::~LogSrv()
{

}

void LogSrv::Init()
{
	logThread.Run();
}

void LogSrv::Exit()
{
	instance.Clear();
	logThread.Exit();
}

LogSrv* LogSrv::GetInstance()
{
	return &instance;
}

void LogSrv::WriteLog(string& log)
{
	ofstream file;
	string path = GetProgramDir() + "log.txt";
	file.open(path, ios::app);
	file << log.c_str() << endl;
	file.close();
}

void LogSrv::Add(string log, ELogType type /*= ELogType::Info*/)
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	char ch[1024] = { 0 };
	sprintf_s(ch, "[%02d] [%02d-%02d-%02d %02d:%02d:%02d %03d] %s", type, t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, log.c_str());

	queueLog.push(ch);
}

bool LogSrv::IsEmpty()
{
	return queueLog.empty();
}

void LogSrv::Clear()
{
	while (!queueLog.empty())
	{
		queueLog.pop();
	}
}

void LogSrv::ProcessLog()
{
	while (!queueLog.empty())
	{
		string log = queueLog.front();
		queueLog.pop();

		WriteLog(log);
	}
}