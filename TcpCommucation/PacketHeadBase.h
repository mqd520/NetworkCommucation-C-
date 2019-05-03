#pragma once

namespace tc
{
	//包头基类定义
	class PacketHeadBase
	{
	public:
		PacketHeadBase();
		~PacketHeadBase();

		//获取包头长度
		virtual int GetHeadLen();

		//获取包体长度
		virtual int GetPacketLen();

		//获取总长度
		virtual int GetTotalLen();

		//获取包命令
		virtual int GetCmd();

		//读取缓冲区数据
		virtual BYTE* Read(int cmd, int len);

		//写入缓冲区数据
		virtual void Write(BYTE* buf, int len);

		//是否可用
		virtual bool IsValid();
	};
}