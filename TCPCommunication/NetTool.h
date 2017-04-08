#pragma once

#include <string>

using namespace std;

namespace TCPCommunication
{
	//************************************
	// Method:    从字节数组中读取多字节字符串
	// FullName:  NetTool::ReadMultiByteStr
	// Access:    public 
	// Returns:   std::string
	// Qualifier:
	// Parameter: 字节数组
	// Parameter: 字节数组长度
	//************************************
	string ReadMultiByteStr(BYTE buf[], int len);

	
	//************************************
	// Method:    从字节数组中读取UTF8字符串
	// FullName:  NetTool::ReadUTF8Str
	// Access:    public 
	// Returns:   std::wstring
	// Qualifier:
	// Parameter: 字节数组
	// Parameter: 字节数组长度
	//************************************
	wstring ReadUTF8Str(BYTE buf[], int len);

	
	//************************************
	// Method:    写入多字节字符串到字节数组
	// FullName:  NetTool::WriteMultiByteStr
	// Access:    public 
	// Returns:   BYTE*
	// Qualifier:
	// Parameter: 多字节字符串
	// Parameter: 字节数组长度(输出)
	//************************************
	BYTE* WriteMultiByteStr(char* str, int* size);

	
	//************************************
	// Method:    写入UTF8字符串到字节数组
	// FullName:  NetTool::WriteUTF8Str
	// Access:    public 
	// Returns:   BYTE*
	// Qualifier:
	// Parameter: UTF8字符串
	// Parameter: 字节数组长度(输出)
	//************************************
	BYTE* WriteUTF8Str(wchar_t* str, int* size);
}
