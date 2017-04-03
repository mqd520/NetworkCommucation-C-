#pragma once

#include <minwindef.h>

namespace ProtocolTool
{
	//************************************
	// Method:    ��ȡָ��ֵ�ĵ�һ���ֽ�
	// FullName:  ProtocolTool::GetFstByteFromInt
	// Access:    public 
	// Returns:   BYTE
	// Qualifier:
	// Parameter: int n
	//************************************
	BYTE GetFstByteFromInt(int n);

	//************************************
	// Method:    ��ȡָ��ֵ�ĵڶ����ֽ�
	// FullName:  ProtocolTool::GetSecByteFromInt
	// Access:    public 
	// Returns:   BYTE
	// Qualifier:
	// Parameter: int n
	//************************************
	BYTE GetSecByteFromInt(int n);

	//************************************
	// Method:    ��ȡָ��ֵ�ĵ������ֽ�
	// FullName:  ProtocolTool::GetTrdByteFromInt
	// Access:    public 
	// Returns:   BYTE
	// Qualifier:
	// Parameter: int n
	//************************************
	BYTE GetTrdByteFromInt(int n);

	//************************************
	// Method:    ��ȡָ��ֵ�ĵ��ĸ��ֽ�
	// FullName:  ProtocolTool::GetFouthByteFromInt
	// Access:    public 
	// Returns:   BYTE
	// Qualifier:
	// Parameter: int n
	//************************************
	BYTE GetFouthByteFromInt(int n);

	//************************************
	// Method:    �ϲ�2���ֽڵ�int
	// FullName:  ProtocolTool::MergeByte
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: ��λ�ֽ�
	// Parameter: ��λ�ֽ�
	//************************************
	int MergeByte(BYTE high, BYTE low);
}