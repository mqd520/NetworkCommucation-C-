#pragma once
#include "Node.h"

namespace NetworkCommunication
{
	class CLinkList
	{
	private:
		size_t m_nCount;//节点数目
		CNode* m_pHead;//头部节点
		CNode* m_pTail;//尾部节点 
		CNode* m_pCurrent;//当前指向节点

	private:
		//************************************
		// Method:    切断2个节点之间关联
		// Parameter: 前节点
		// Parameter: 后节点
		//************************************
		void CutoffRelation(CNode* pPrev, CNode* pNext);

	public:
		CLinkList();
		~CLinkList();

		//************************************
		// Method:    获取所有节点数
		//************************************
		size_t Count();

		//************************************
		// Method:    获取头部节点
		//************************************
		CNode* GetHead();

		//************************************
		// Method:    获取尾部节点
		//************************************
		CNode* GetTail();

		//************************************
		// Method:    获取当前指向的节点
		//************************************
		CNode* GetCurrent();

		//************************************
		// Method:    指向下一个节点
		// Returns:   指向是否成功
		//************************************
		bool MoveNext();

		//************************************
		// Method:    重置当前指向
		//************************************
		void Reset();

		//************************************
		// Method:    从尾部压入一个节点
		// Parameter: 新节点
		//************************************
		void PushBack(CNode* pNode);

		//************************************
		// Method:    从头部压入一个节点
		// Parameter: 新节点
		//************************************
		void PushFront(CNode* pNode);

		//************************************
		// Method:    弹出头部节点
		// Returns:   头部节点
		//************************************
		CNode* PopHead();

		//************************************
		// Method:    弹出尾部节点
		// Returns:   尾部节点
		//************************************
		CNode* PopTail();

		//************************************
		// Method:    清除所有节点
		//************************************
		void Clear();
	};
}