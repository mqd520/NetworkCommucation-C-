#pragma once

namespace tc
{
	class CThreadEvent
	{
	private:
		HANDLE m_hEvent;

	public:
		CThreadEvent(bool bManualReset = true, bool bInitialState = false);
		~CThreadEvent();

		HANDLE GetEvent() const;

		void Wait() const;

		bool Wait(DWORD timeoutMillis) const;

		void Active();

		void Inactive();
	};
}