#pragma once

#include <Stringapiset.h>
#include <string>

using namespace std;

//从字节数组中读取多字节字符串
string ReadMultiByteStr(BYTE buf[], int len);

//从字节数组中读取UTF8字符串
wstring ReadUTF8Str(BYTE buf[], int len);

//写入多字节字符串到字节数组
BYTE* WriteMultiByteStr(char* str);

//写入UTF8字符串到字节数组
BYTE* WriteUTF8Str(wchar_t* str, int* size);
