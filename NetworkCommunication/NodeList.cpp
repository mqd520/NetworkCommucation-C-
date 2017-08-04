#include "stdafx.h"
#include "NodeList.h"

namespace NetworkCommunication
{
	CNodeList::CNodeList()
		: m_pHead(0)
		, m_pTail(0)
		, m_nNodes(0)
	{
	}

	void CNodeList::PushNode(CNode *pNode)
	{
		pNode->AddToList((CNodeList*)this);
		pNode->Prev(m_pTail);
		if (!m_pHead)
		{
			m_pHead = pNode;
		}
		m_pTail = pNode;
		++m_nNodes;
	}

	void CNodeList::PushFront(CNode *pNode)
	{
		pNode->AddToList((CNodeList*)this);

		pNode->Next(m_pHead);

		m_pHead = pNode;

		if (!m_pTail)
		{
			m_pTail = m_pHead;
		}

		++m_nNodes;
	}

	CNode *CNodeList::PopNode()
	{
		CNode *pNode = m_pHead;

		if (pNode)
		{
			RemoveNode(pNode);
		}

		return pNode;
	}

	CNode* CNodeList::Head() const
	{
		return m_pHead;
	}


	CNode* CNodeList::End() const
	{
		return m_pTail;
	}

	size_t CNodeList::Count() const
	{
		return m_nNodes;
	}

	bool CNodeList::Empty() const
	{
		return (0 == m_nNodes);
	}

	void CNodeList::RemoveNode(CNode *pNode)
	{
		if (pNode == m_pHead)
		{
			//lint -e{613} Possible use of null pointer 
			m_pHead = pNode->Next();
		}
		if (pNode == m_pTail)
		{
			m_pTail = pNode->Prev();
		}

		//lint -e{613} Possible use of null pointer 
		pNode->Unlink();

		--m_nNodes;
	}
}