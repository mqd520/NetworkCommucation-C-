#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

//#include <tchar.h>
#include <Stringapiset.h>
#include <WinSock2.h>
#include <string>

using namespace std;

//多字节转UTF-8
wstring MultiByteToUTF8(const char* str);
//UTF-8转多字节
string UTF8ToMultiByte(const wchar_t* str);
//获取本地IP
bool GetLocalIP(TCHAR* ip);