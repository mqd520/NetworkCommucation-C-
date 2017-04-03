#include "stdafx.h"
#include "Protocol1Handle.h"
#include <stdio.h>

using namespace Protocol1;

CProtocol1Handle::CProtocol1Handle()
{

}

CProtocol1Handle::~CProtocol1Handle()
{

}

//���
LPPackage1 CProtocol1Handle::Packet(Package1Type type, BYTE buf[], int len)
{
	LPPackage1 pack = new Package1;
	pack->highDataLen = GetHighByte(len);
	pack->lowDataLen = GetLowerByte(len);
	pack->highPackType = GetHighByte(type);
	pack->lowPackType = GetLowerByte(type);
	pack->data = new BYTE[len];
	memcpy(pack->data, buf, len);
	return pack;
}

//��ȡ��λ�ֽ�
BYTE CProtocol1Handle::GetHighByte(int n)
{
	return (BYTE)(n >> 8);
}

//��ȡ��λ�ֽ�
BYTE CProtocol1Handle::GetLowerByte(int n)
{
	return (BYTE)((n << 24) >> 24);
}

//��ȡ���ܳ���
int CProtocol1Handle::GetPackageLen(int datalen)
{
	return HeadLen + datalen;
}

//��ȡ��ͷ����
int CProtocol1Handle::GetHeadLen()
{
	return HeadLen;
}

//���
LPPackage1 CProtocol1Handle::UnPacket(BYTE buf[], int len)
{
	LPPackage1 p = new Package1;
	if (len > HeadLen)
	{
		p->data = new BYTE[len - HeadLen];
		memcpy(p, buf, HeadLen);
		memcpy(p->data, buf + HeadLen, len - HeadLen);
	}
	return p;
}

//��ȡ�������ݳ���
int CProtocol1Handle::GetDataLen(LPPackage1 pack)
{
	return (int)(pack->highDataLen << 8) + (int)pack->lowDataLen;
}

//�ͷŰ��ڴ�
bool CProtocol1Handle::ReleaseMemory(LPPackage1 pack)
{
	if (pack)
	{
		if (pack->data)
		{
			delete pack->data;
			pack->data = NULL;
		}
		delete pack;
		pack = NULL;
	}
	return true;
}

//��ȡ���ֽڻ�����
BYTE* CProtocol1Handle::GetBuffer(LPPackage1 pack)
{
	int len = GetLen(pack);
	int datalen = GetDataLen(pack);
	BYTE* buf = new BYTE[len];
	memcpy(buf, pack, HeadLen);
	memcpy(buf + HeadLen, pack->data, datalen);
	return buf;
}

//��ȡ���ܳ���
int CProtocol1Handle::GetLen(LPPackage1 pack)
{
	return HeadLen + GetDataLen(pack);
}