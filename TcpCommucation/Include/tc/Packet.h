#pragma once
#include "NetworkStreamRead.h"
#include "NetworkStreamWrite.h"

namespace tc
{
	// 包体基类
	class Packet
	{
	public:
		Packet(int cmd);

	protected:
		int pckCmd;		// 包命令

	public:
		//************************************
		// Method:    获取包命令
		//************************************
		virtual int GetCmd();

		//************************************
		// Method:    获取包长度(不含包头)
		//************************************
		virtual int GetLen();

		//************************************
		// Method:    从流中读取数据到包中
		// Parameter: ns:	只读网络流对象
		//************************************
		virtual void Read(NetworkStreamRead& ns);

		//************************************
		// Method:    从流中读取数据到包中
		// Parameter: pBuf:	缓冲区
		// Parameter: len:	缓冲区长度
		// Parameter: bigEndian:	是否使用大端字节序
		//************************************
		virtual void Read1(BYTE* pBuf, int len, bool bigEndian = true);

		//************************************
		// Method:    向流中写入数据
		// Parameter: ns:	只写网络流对象
		//************************************
		virtual void Write(NetworkStreamWrite& ns);

		//************************************
		// Method:    向流中写入数据
		// Parameter: pBuf:	缓冲区
		// Parameter: len:	缓冲区长度
		// Parameter: bigEndian:	是否使用大端字节序
		//************************************
		virtual void Write1(BYTE* pBuf, int len, bool bigEndian = true);
	};
}