#include "stdafx.h"
#include "LogSrv.h"

string GetProgramDir()
{
	char exeFullPath[MAX_PATH] = { 0 };

	GetModuleFileNameA(NULL, exeFullPath, MAX_PATH);
	string strPath = exeFullPath;
	int pos = strPath.find_last_of('\\', strPath.length());
	return strPath.substr(0, pos + 1);
}

LogSrv::LogSrv()
{

}

LogSrv::~LogSrv()
{

}

void LogSrv::Add(string log)
{
	ofstream file;
	string path = GetProgramDir() + "log.txt";
	file.open(path, ios::app);
	file << log.c_str() << endl;
	file.close();
}