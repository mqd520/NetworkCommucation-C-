#pragma once
#include "Node.h"

class CNode;

namespace NetworkCommunication
{
	//节点列表
	class CNodeList
	{
	private:
		CNode* m_pHead;
		CNode* m_pTail;
		size_t m_nNodes;

	public:
		CNodeList();

		void PushNode(CNode* pNode);

		void PushFront(CNode* pNode);

		CNode* PopNode();

		CNode* Head() const;

		CNode* End() const;

		size_t Count() const;

		bool Empty() const;

		void RemoveNode(CNode* pNode);
	};
}