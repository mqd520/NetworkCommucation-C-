#pragma once

namespace tc
{
	class CNode
	{
	private:
		CNode* m_pPrev;
		CNode* m_pNext;

	protected:
		CNode();

	public:
		~CNode();

		CNode* GetPrev();

		CNode* GetNext();

		bool IsHead();

		bool IsTail();

		void SetPrev(CNode* pPrev);

		void SetNext(CNode* pNext);
	};
}