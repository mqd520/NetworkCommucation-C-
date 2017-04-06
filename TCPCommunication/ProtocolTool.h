#pragma once

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
	// Method:    �ϲ��ֽڵ�int
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
	// Method:    �Ӷ��ֽ��ַ����������л�ȡ�ַ�����
	// FullName:  ProtocolTool::GetLenFromMultiByteBuf
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: ���ֽ��ַ���������
	// Parameter: ��ʼλ��
	// Parameter: ����λ��
	//************************************
	int GetLenFromMultiByteBuf(BYTE* buf, int start, int end);
}