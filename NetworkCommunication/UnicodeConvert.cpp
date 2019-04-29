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
		int count = 0;	// UTF16�ֽ�����

		while (index < len)
		{
			if (index1 == 0)
			{
				memset(tmp, 0, 4);
				BYTE prefix = pBufSrc[index] >> 4;	// ��ȡ���ֽڸ�4λ
				if ((BYTE)(prefix >> 3) == 0)	// ��ʾ���ֽ��ַ���
				{
					size = 1;
				}
				else if (prefix == 6)	// ��ʾ2�ֽ��ַ���
				{
					size = 2;
				}
				else if (prefix == 14)	// ��ʾ3�ֽ��ַ���
				{
					size = 3;
				}
				else if (prefix == 15)	// ��ʾ4�ֽ��ַ���
				{
					size = 4;
				}
				tmp[index1] = (UINT)(((BYTE)(pBufSrc[index] << size)) >> size);
			}
			else
			{
				tmp[index1] = (UINT)(((BYTE)(pBufSrc[index] << 2)) >> 2);//ȥ����λ10
			}

			index++;

			index1++;
			if (index1 == size)
			{
				index1 = 0;

				//�����unicode��Ӧֵ
				UINT encode = tmp[size - 1];
				int step = 1;
				for (int i = size - 2; i > -1; i--)
				{
					encode |= tmp[i] << (step * 6);
					step++;
				}

				if (bBigEndian)	// ����ֽ���
				{
					pBufDest[index2++] = (BYTE)(encode >> 8);
					pBufDest[index2++] = (BYTE)((encode << 24) >> 24);
				}
				else // С���ֽ���
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