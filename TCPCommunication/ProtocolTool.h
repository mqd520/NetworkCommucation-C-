#pragma once

namespace ProtocolTool
{
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
}