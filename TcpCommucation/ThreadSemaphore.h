#pragma once

namespace NetworkCommunication
{
	class CThreadSemaphore
	{
	private:
		HANDLE m_hSemaphore;

	public:
		CThreadSemaphore(LONG lInitialCount, LONG lMaximumCount = 4096, LPCTSTR lpName = NULL);

		~CThreadSemaphore();

		void Down() const;

		void Up() const;
	};
}