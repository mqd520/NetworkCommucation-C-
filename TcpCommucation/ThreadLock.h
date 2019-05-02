#pragma once

namespace NetworkCommunication
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