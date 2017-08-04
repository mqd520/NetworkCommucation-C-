#include "stdafx.h"
#include "LinkList.h"

namespace NetworkCommunication
{
	CLinkList::CLinkList() :
		m_nCount(0),
		m_pHead(NULL),
		m_pTail(NULL),
		m_pCurrent(NULL)
	{

	}

	CLinkList::~CLinkList()
	{

	}

	void CLinkList::CutoffRelation(CNode* pPrev, CNode* pNext)
	{
		if (pPrev != NULL && pNext != NULL)
		{
			pPrev->SetNext(NULL);
			pNext->SetPrev(NULL);
		}
	}

	size_t CLinkList::Count()
	{
		return m_nCount;
	}

	CNode* CLinkList::GetHead()
	{
		return m_pHead;
	}

	CNode* CLinkList::GetTail()
	{
		return m_pTail;
	}

	CNode* CLinkList::GetCurrent()
	{
		return m_pCurrent;
	}

	bool CLinkList::MoveNext()
	{
		bool result = false;
		if (m_pCurrent == NULL)
		{
			if (m_pHead != NULL)
			{
				m_pCurrent = m_pHead;
				result = true;
			}
		}
		else if (m_pCurrent->GetNext() != NULL)
		{
			m_pCurrent = m_pCurrent->GetNext();
			result = true;
		}
		return result;
	}

	void CLinkList::Reset()
	{
		m_pCurrent = NULL;
	}

	void CLinkList::PushBack(CNode* pNode)
	{
		if (pNode != NULL){
			if (m_nCount == 0)
			{
				m_pHead = m_pTail = pNode;
			}
			else
			{
				pNode->SetPrev(m_pTail);
				m_pTail = pNode;
			}
			m_nCount++;
		}
	}

	void CLinkList::PushFront(CNode* pNode)
	{
		if (pNode != NULL){
			if (m_nCount == 0)
			{
				m_pHead = m_pTail = pNode;
			}
			else
			{
				pNode->SetNext(m_pHead);
				m_pHead = pNode;
			}
			m_nCount++;
		}
	}

	CNode* CLinkList::PopHead()
	{
		CNode* p = m_pHead;
		if (m_pHead != NULL)
		{
			m_pHead = m_pHead->GetNext();
			CutoffRelation(p, m_pHead);
			m_nCount--;
		}
		return p;
	}

	CNode* CLinkList::PopTail()
	{
		CNode* p = m_pTail;
		if (m_pTail != NULL)
		{
			m_pTail = m_pTail->GetPrev();
			CutoffRelation(m_pTail, p);
			m_nCount--;
		}
		return p;
	}

	void CLinkList::Clear()
	{

	}
}