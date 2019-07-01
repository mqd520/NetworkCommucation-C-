#include "stdafx.h"
#include "Include/tc/Node.h"

namespace tc
{
	CNode::CNode() :
		m_pNext(NULL),
		m_pPrev(NULL)
	{

	}

	CNode::~CNode()
	{

	}

	CNode* CNode::GetPrev()
	{
		return m_pPrev;
	}

	CNode* CNode::GetNext()
	{
		return m_pNext;
	}

	bool CNode::IsHead()
	{
		return m_pPrev == NULL;
	}

	bool CNode::IsTail()
	{
		return m_pNext == NULL;
	}

	void CNode::SetPrev(CNode* pPrev)
	{
		m_pPrev = pPrev;
		if (pPrev != NULL && pPrev->GetNext() != this)
		{
			pPrev->SetNext(this);
		}
	}

	void CNode::SetNext(CNode* pNext)
	{
		m_pNext = pNext;
		if (pNext != NULL && pNext->GetPrev() != this)
		{
			pNext->SetPrev(this);
		}
	}
}