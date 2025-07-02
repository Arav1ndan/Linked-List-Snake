#include "LinkedListLib/LinkedList.h"

namespace LinkedListLib
{
	int LinkedList::findMiddleNode()
	{
		Node* slow = head_node;
		Node* fast = head_node;
		int midIndex = 0;

		while (fast != nullptr && fast->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;
			midIndex++;
		}
		return midIndex;
	}
}