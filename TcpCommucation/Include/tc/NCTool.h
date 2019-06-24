#pragma once
#include <string>

using namespace std;

namespace tc
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

		//************************************
		// Method:    翻转缓冲区
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: int len:		缓冲区长度
		//************************************
		static void ReverseBuf(BYTE* pBuf, int len);

		//************************************
		// Method:    创建一个随机数
		// Parameter: min: 最小值
		// Parameter: max: 最大值
		//************************************
		static int CreateRand(unsigned int min = 0, unsigned int max = 0);

	private:

	};
}

