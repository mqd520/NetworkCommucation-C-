#pragma once

#include "Package1.h"

namespace Protocol1
{
	class CProtocol1Handle
	{
	public:
		CProtocol1Handle();
		~CProtocol1Handle();

		//��ȡ���ܳ���
		int GetLen(LPPackage1 pack);

		//��ȡ��ͷ����
		int GetHeadLen();

		//��ȡ�������ݳ���
		int GetDataLen(LPPackage1 pack);

		//�ͷŰ��ڴ�
		bool ReleaseMemory(LPPackage1 pack);

		//��ȡ���ֽڻ�����
		BYTE* GetBuffer(LPPackage1 pack);

		//���
		LPPackage1 UnPacket(BYTE buf[], int len);

		//���
		LPPackage1 Packet(Package1Type type, BYTE buf[], int len);
	protected:
		//��ȡ��λ�ֽ�
		BYTE GetHighByte(int n);

		//��ȡ��λ�ֽ�
		BYTE GetLowerByte(int n);

		//��ȡ���ܳ���
		int GetPackageLen(int datalen);
	};
}