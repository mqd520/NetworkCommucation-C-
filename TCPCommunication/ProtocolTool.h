#pragma once

#include <minwindef.h>

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
	// Method:    合并2个字节到int
	// FullName:  ProtocolTool::MergeByte
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: 高位字节
	// Parameter: 低位字节
	//************************************
	int MergeByte(BYTE high, BYTE low);
}