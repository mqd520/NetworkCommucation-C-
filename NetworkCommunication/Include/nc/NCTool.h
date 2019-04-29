#pragma once

namespace NetworkCommunication
{
	// 字节序枚举值定义
	enum EByteOrder
	{
		litte = 1,	// 小端字节序
		big = 2		// 大端字节序
	};

	class NCTool
	{
	public:
		NCTool();
		~NCTool();

	public:
		//************************************
		// Method:    获取当前主机字节序
		// Access:    public static 
		// Returns:   EByteOrder
		//************************************
		static EByteOrder GetHostByteOrder();

	private:

	};
}

