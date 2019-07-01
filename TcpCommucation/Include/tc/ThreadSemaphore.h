#pragma once

namespace tc
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