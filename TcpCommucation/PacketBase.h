#pragma once

namespace NetworkCommunication
{
	//包体基类
	class PacketBase
	{
	public:
		PacketBase();
		~PacketBase();

		//获取包命令
		virtual int GetCmd();

		//从包中读取数据到缓冲区
		//len	缓冲区长度
		//return	缓冲区
		virtual BYTE* Read(int* len);

		//从网络缓冲区中写入数据到包中
		//buf:	网络缓冲区
		//len	网络缓冲区长度
		virtual void Write(BYTE* buf, int len);

		//释放资源
		virtual void Release();
	};
}