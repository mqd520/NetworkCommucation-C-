#pragma once

#include "Package1.h"

namespace Protocol1
{
	class CProtocol1Handle
	{
	public:
		CProtocol1Handle();
		~CProtocol1Handle();

		//获取包总长度
		int GetLen(LPPackage1 pack);

		//获取包头长度
		int GetHeadLen();

		//获取包体数据长度
		int GetDataLen(LPPackage1 pack);

		//释放包内存
		bool ReleaseMemory(LPPackage1 pack);

		//获取包字节缓冲区
		BYTE* GetBuffer(LPPackage1 pack);

		//解包
		LPPackage1 UnPacket(BYTE buf[], int len);

		//封包
		LPPackage1 Packet(Package1Type type, BYTE buf[], int len);
	protected:
		//获取高位字节
		BYTE GetHighByte(int n);

		//获取地位字节
		BYTE GetLowerByte(int n);

		//获取包总长度
		int GetPackageLen(int datalen);
	};
}