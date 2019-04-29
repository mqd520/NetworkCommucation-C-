#include "stdafx.h"
#include "UnicodeConvert.h"

namespace NetworkCommunication
{
	int UTF8ByteToUTF16Byte(BYTE* pBufSrc, int len, BYTE* pBufDest, bool bBigEndian/* = true*/)
	{
		UINT tmp[4] = { 0 };
		int index = 0;
		int index1 = 0;
		int index2 = 0;
		int size = 0;
		int count = 0;	// UTF16字节总数

		while (index < len)
		{
			if (index1 == 0)
			{
				memset(tmp, 0, 4);
				BYTE prefix = pBufSrc[index] >> 4;	// 获取首字节高4位
				if ((BYTE)(prefix >> 3) == 0)	// 表示单字节字符串
				{
					size = 1;
				}
				else if (prefix == 6)	// 表示2字节字符串
				{
					size = 2;
				}
				else if (prefix == 14)	// 表示3字节字符串
				{
					size = 3;
				}
				else if (prefix == 15)	// 表示4字节字符串
				{
					size = 4;
				}
				tmp[index1] = (UINT)(((BYTE)(pBufSrc[index] << size)) >> size);
			}
			else
			{
				tmp[index1] = (UINT)(((BYTE)(pBufSrc[index] << 2)) >> 2);//去除高位10
			}

			index++;

			index1++;
			if (index1 == size)
			{
				index1 = 0;

				//计算出unicode对应值
				UINT encode = tmp[size - 1];
				int step = 1;
				for (int i = size - 2; i > -1; i--)
				{
					encode |= tmp[i] << (step * 6);
					step++;
				}

				if (bBigEndian)	// 大端字节序
				{
					pBufDest[index2++] = (BYTE)(encode >> 8);
					pBufDest[index2++] = (BYTE)((encode << 24) >> 24);
				}
				else // 小端字节序
				{
					pBufDest[index2++] = (BYTE)((encode << 24) >> 24);
					pBufDest[index2++] = (BYTE)(encode >> 8);
				}
				count += 2;
			}
		}

		return count;
	}
}