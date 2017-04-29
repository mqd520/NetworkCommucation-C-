#pragma once

namespace NetworkCommunication
{
	//�������
	class PacketBase
	{
	public:
		PacketBase();
		~PacketBase();

		//��ȡ������
		virtual int GetCmd();

		//�Ӱ��ж�ȡ���ݵ�������
		//len	����������
		//return	������
		virtual BYTE* Read(int* len);

		//�����绺������д�����ݵ�����
		//buf:	���绺����
		//len	���绺��������
		virtual void Write(BYTE* buf, int len);

		//�ͷ���Դ
		virtual void Release();
	};
}