#pragma once

namespace NetworkCommunication
{
	//泛型成员函数指针
	template<typename T>
	class CTFunPointer
	{
	public:
		CTFunPointer(){};
		~CTFunPointer(){};

		//无参无返回值
		typedef void(T::*Fun1)();
	};
}