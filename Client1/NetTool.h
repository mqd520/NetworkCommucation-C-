#pragma once

#include <Stringapiset.h>
#include <string>

using namespace std;

//���ֽ������ж�ȡ���ֽ��ַ���
string ReadMultiByteStr(BYTE buf[], int len);

//���ֽ������ж�ȡUTF8�ַ���
wstring ReadUTF8Str(BYTE buf[], int len);

//д����ֽ��ַ������ֽ�����
BYTE* WriteMultiByteStr(char* str);

//д��UTF8�ַ������ֽ�����
BYTE* WriteUTF8Str(wchar_t* str, int* size);
