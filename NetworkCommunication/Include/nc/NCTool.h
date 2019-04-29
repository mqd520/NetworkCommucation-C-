#pragma once

namespace NetworkCommunication
{
	// �ֽ���ö��ֵ����
	enum EByteOrder
	{
		litte = 1,	// С���ֽ���
		big = 2		// ����ֽ���
	};

	class NCTool
	{
	public:
		NCTool();
		~NCTool();

	public:
		//************************************
		// Method:    ��ȡ��ǰ�����ֽ���
		// Access:    public static 
		// Returns:   EByteOrder
		//************************************
		static EByteOrder GetHostByteOrder();

	private:

	};
}

