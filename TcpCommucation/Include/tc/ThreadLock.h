#pragma once

namespace tc
{
	class CThreadLock
	{
	private:
		CRITICAL_SECTION m_crSection;

	public:
		CThreadLock();
		virtual ~CThreadLock();

	public:
		void Lock();

		void Unlock();
	};
}