#pragma once
#include "NetworkStreamRead.h"
#include "NetworkStreamWrite.h"

namespace tc
{
	// 包头基类定义
	class PacketHead
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: cmd:	包命令
		// Parameter: len:	包体长度
		//************************************
		PacketHead(int cmd, int len);

	protected:
		int nHeadLen;			// 包头长度
		int nCmd;				// 包命令
		int nLen;				// 包长度
		int nTotalLen;			// 包总长度

	public:
		//************************************
		// Method:    获取包头长度
		//************************************
		virtual int GetHeadLen();

		//************************************
		// Method:    获取包体长度
		//************************************
		virtual int GetPacketLen();

		//************************************
		// Method:    获取总长度
		//************************************
		virtual int GetTotalLen();

		//************************************
		// Method:    获取包命令
		//************************************
		virtual int GetCmd();

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

		//************************************
		// Method:    是否可用
		//************************************
		virtual bool IsValid();
	};
}