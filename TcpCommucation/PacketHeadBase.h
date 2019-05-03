#pragma once

namespace tc
{
	//��ͷ���ඨ��
	class PacketHeadBase
	{
	public:
		PacketHeadBase();
		~PacketHeadBase();

		//��ȡ��ͷ����
		virtual int GetHeadLen();

		//��ȡ���峤��
		virtual int GetPacketLen();

		//��ȡ�ܳ���
		virtual int GetTotalLen();

		//��ȡ������
		virtual int GetCmd();

		//��ȡ����������
		virtual BYTE* Read(int cmd, int len);

		//д�뻺��������
		virtual void Write(BYTE* buf, int len);

		//�Ƿ����
		virtual bool IsValid();
	};
}