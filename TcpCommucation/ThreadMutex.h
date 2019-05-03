#pragma once

namespace tc
{
	class CThreadMutex
	{
	private:
		HANDLE m_hMutex;

	public:
		CThreadMutex(BOOL bInitialOwner, LPCTSTR lpName);
		~CThreadMutex(void);

		HANDLE GetHandle() const;

		void RetrieveOwner() const;

		bool Wait(DWORD timeoutMillis) const;

		void Release();
	};
}