#pragma once

#include <string>

using namespace std;

namespace tc
{
	//************************************
	// Method:    多字节字符串转UTF8字符串
	// FullName:  Common::MultiByteToUTF8
	// Access:    public 
	// Returns:   std::wstring
	// Qualifier:
	// Parameter: const char * str
	//************************************
	wstring MultiByteToUTF8(const char* str);

	//************************************
	// Method:    UTF8字符串转多字节字符串
	// FullName:  Common::UTF8ToMultiByte
	// Access:    public 
	// Returns:   std::string
	// Qualifier:
	// Parameter: const wchar_t * str
	//************************************
	string UTF8ToMultiByte(const wchar_t* str);

	//************************************
	// Method:    获取多字节字符串字节数
	// FullName:  NetTool::GetStrByteCount
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: TCHAR * str
	//************************************
	int GetAStrByteCount(char* str);

	//************************************
	// Method:    获取宽字节字符串字节数
	// FullName:  NetTool::GetStrByteCount
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: TCHAR * str
	//************************************
	int GetWStrByteCount(wchar_t* str);

	//************************************
	// Method:    获取字符串字节数
	// FullName:  Common::GetStrByteCount
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: TCHAR * str
	//************************************
	int GetStrByteCount(TCHAR* str);

	//************************************
	// Method:    获取指定值的第一个字节
	// FullName:  ProtocolTool::GetFstByteFromInt
	// Access:    public 
	// Returns:   BYTE
	// Qualifier:
	// Parameter: int n
	//************************************
	BYTE GetFstByteFromInt(int n);

	//************************************
	// Method:    获取指定值的第二个字节
	// FullName:  ProtocolTool::GetSecByteFromInt
	// Access:    public 
	// Returns:   BYTE
	// Qualifier:
	// Parameter: int n
	//************************************
	BYTE GetSecByteFromInt(int n);

	//************************************
	// Method:    获取指定值的第三个字节
	// FullName:  ProtocolTool::GetTrdByteFromInt
	// Access:    public 
	// Returns:   BYTE
	// Qualifier:
	// Parameter: int n
	//************************************
	BYTE GetTrdByteFromInt(int n);

	//************************************
	// Method:    获取指定值的第四个字节
	// FullName:  ProtocolTool::GetFouthByteFromInt
	// Access:    public 
	// Returns:   BYTE
	// Qualifier:
	// Parameter: int n
	//************************************
	BYTE GetFouthByteFromInt(int n);

	//************************************
	// Method:    合并字节到int
	// FullName:  ProtocolTool::MergeByte
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: BYTE fouth
	// Parameter: BYTE trd
	// Parameter: BYTE sec
	// Parameter: BYTE fst
	//************************************
	int MergeByte(BYTE fouth = 0, BYTE trd = 0, BYTE sec = 0, BYTE fst = 0);

	//************************************
	// Method:    从多字节字符串缓冲区中获取字符个数
	// FullName:  ProtocolTool::GetLenFromMultiByteBuf
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: 多字节字符串缓冲区
	// Parameter: 起始位置
	// Parameter: 结束位置
	//************************************
	int GetLenFromMultiByteBuf(BYTE* buf, int start, int end);

	//************************************
	// Method:    写入int类型数据到缓冲区
	// FullName:  NetworkCommunication::ReadValue
	// Access:    public 
	// Returns:   缓冲区
	// Qualifier:
	// Parameter: 值
	// Parameter: 是否使用小字节序(网络字节序)
	//************************************
	BYTE* WriteIntToBuf(int val, bool bLittleEndian = true);

	//************************************
	// Method:    写入short类型数据到缓冲区
	// FullName:  NetworkCommunication::ReadValue
	// Access:    public 
	// Returns:   缓冲区
	// Qualifier:
	// Parameter: 值
	// Parameter: 是否使用小字节序(网络字节序)
	//************************************
	BYTE* WriteShortToBuf(short val, bool bLittleEndian = true);

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
	wstring ReadUTF8ByteStr(BYTE buf[], int len);

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