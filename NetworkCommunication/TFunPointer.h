#pragma once

namespace NetworkCommunication
{
	//���ͳ�Ա����ָ��
	template<typename T>
	class CTFunPointer
	{
	public:
		CTFunPointer(){};
		~CTFunPointer(){};

		//�޲��޷���ֵ
		typedef void(T::*Fun1)();
	};
}