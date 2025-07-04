#include "LinkedListLib/SingleLinked/SingleLinkedList.h"
#include "LinkedListLib/SingleLinked/SingleNode.h"
#include "Player/BodyPart.h"
#include "Level/LevelView.h"
#include <iostream>

namespace LinkedListLib {

	namespace SingleLinked
	{
		SingleLinkedList::SingleLinkedList()
		{
			head_node = nullptr;
		}

		SingleLinkedList::~SingleLinkedList() = default;

		Node* SingleLinkedList::createNode()
		{
			return new Node();
		}

		void SingleLinkedList::insertNodeAtHead()
		{
			linked_list_size++;
			Node* new_node = createNode();

			if (head_node == nullptr)
			{
				head_node = new_node;
				initializeNode(new_node, nullptr, Operation::HEAD);
				return;
			}

			initializeNode(new_node, head_node, Operation::HEAD);
			new_node->next = head_node;
			head_node = new_node;
		}
		void SingleLinkedList::insertNodeAtTail()
		{
			linked_list_size++;
			Node* new_node = createNode();

			Node* cur_node = head_node;

			if (cur_node == nullptr)
			{
				head_node = new_node;
				initializeNode(new_node, nullptr, Operation::TAIL);
				return;
			}

			while (cur_node->next != nullptr)
			{
				cur_node = cur_node->next;
			}

			cur_node->next = new_node;

			initializeNode(new_node, cur_node, Operation::TAIL);
		}
		void SingleLinkedList::insertNodeAtMiddle()
		{
			if (head_node == nullptr)
			{
				insertNodeAtHead();
				return;
			}
			int middle_index = findMiddleNode();

			Node* new_node = createNode();
			insertNodeAtIndex(middle_index, new_node);
		}
		void SingleLinkedList::insertNodeAtIndex(int index, Node* new_node)
		{

		}
		void SingleLinkedList::shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node)
		{
			Node* next_node = cur_node;
			cur_node = new_node;

			while (cur_node != nullptr && next_node != nullptr)
			{
				cur_node->body_part.setPosition(next_node->body_part.getPosition());
				cur_node->body_part.setDirection(next_node->body_part.getDirection());

				prev_node = cur_node;
				cur_node = next_node;
				next_node = next_node->next;
			}

			initializeNode(cur_node, prev_node, Operation::TAIL);
		}
	/*	sf::Vector2i SingleLinkedList::getNewNodePosition(Node* reference_node, Operation operation)
		{
			switch (operation)
			{
			case LinkedList::Operation::HEAD:
				return reference_node->body_part.getNextPosition();
			case LinkedList::Operation::TAIL:
				return reference_node->body_part.getPrevPosition();
			}
			return default_position;

		}
		bool SingleLinkedList::processNodeCollision()
		{
			if (head_node == nullptr) {
				return false;
			}
			sf::Vector2i predicted_position = head_node->body_part.getNextPosition();

			Node* cur_node = head_node->next;

			while (cur_node != nullptr)
			{
				if (cur_node->body_part.getNextPosition() == predicted_position) {
					return true;
				}
				cur_node = cur_node->next;
			}

			return false;
		}*/

		
		void SingleLinkedList::removeAllNodes()
		{
			if (head_node == nullptr)return;

			while (head_node != nullptr);
			{
				removeNodeAtHead();
			}
		}
		void SingleLinkedList::removeNodeAtHead()
		{
			Node* cur_node = head_node;
			head_node = head_node->next;

			cur_node->next = nullptr;
			delete(cur_node);
			linked_list_size--;
		}

		void SingleLinkedList::removeNodeAtIndex(int index)
		{
			if (index < 0 || index >= linked_list_size)return;

			int cur_index = 0;
			Node* cur_node = head_node;
			Node* pre_node = nullptr;

			while (cur_node != nullptr && cur_index < index)
			{
				pre_node = cur_node;
				cur_node = cur_node->next;
				cur_index++;
			}

			pre_node->next = cur_node->next;
			shiftNodesAfterRemoval(cur_node);
			delete(cur_node);
			linked_list_size--;
		}

		void SingleLinkedList::removeNodeAt(int index)
		{
			if (index < 0 || index >= linked_list_size)return;

			if (index == 0)
			{
				removeNodeAtHead();
			}
			else
			{
				removeNodeAtIndex(index);
			}
		}

		void SingleLinkedList::removeNodeAtMiddle()
		{
			if (head_node == nullptr)return;
			int middle_index = findMiddleNode();
			removeNodeAt(middle_index);
		}

		void SingleLinkedList::removeNodeAtTail()
		{
			if (head_node == nullptr)return;
			linked_list_size--;

			Node* cur_node = head_node;

			if (cur_node->next == nullptr)
			{
				removeNodeAtHead();
				return;
			}

			while (cur_node->next->next != nullptr)
			{
				cur_node = cur_node->next;
			}
			delete(cur_node->next);
			cur_node->next = nullptr;
		}

		void SingleLinkedList::removeHalfNodes()
		{
			if (linked_list_size <= 1) return;
			int half_length = linked_list_size / 2;
			int new_tail_index = half_length - 1;

			Node* prev_node = findNodeAtIndex(new_tail_index);
			Node* cur_node = prev_node->next;

			while (cur_node != nullptr)
			{
				Node* node_to_delete = cur_node;
				cur_node = cur_node->next;

				delete (node_to_delete);
				linked_list_size--;
			}

			prev_node->next = nullptr;
		}

		Direction SingleLinkedList::reverse()
		{
			Node* cur_node = head_node;
			Node* prev_node = nullptr;
			Node* next_node = nullptr;

			while (cur_node != nullptr)
			{
				next_node = cur_node->next;
				cur_node->next = prev_node;

				prev_node = cur_node;
				cur_node = next_node;
			}

			head_node = prev_node;

			reverseNodeDirections();
			return head_node->body_part.getDirection();
		}

		/*Direction SingleLinkedList::getReverseDirection(Direction reference_direction)
		{
			switch (reference_direction)
			{
			case Player::Direction::UP:
				return Direction::DOWN;
			case Player::Direction::DOWN:
				return Direction::UP;
			case Player::Direction::LEFT:
				return Direction::RIGHT;
			case Player::Direction::RIGHT:
				return Direction::LEFT;
			}
		}*/

		/*void SingleLinkedList::reverseNodeDirections()
		{
			Node* curr_node = head_node;

			while (curr_node != nullptr)
			{
				curr_node->body_part.setDirection(getReverseDirection(curr_node->body_part.getPrevDirection()));
				curr_node = curr_node->next;
			}
		}

		Node* SingleLinkedList::findNodeAtIndex(int index)
		{
			int cur_index = 0;

			Node* cur_node = head_node;
			Node* prev_node = nullptr;

			while (cur_node != nullptr && cur_index <= index)
			{
				prev_node = cur_node;
				cur_node = cur_node->next;
				cur_index++;
			}
			return prev_node;
		}

		std::vector<sf::Vector2i> SingleLinkedList::getNodesPositionList()
		{
			std::vector<sf::Vector2i> nodes_position_list;

			Node* cur_node = head_node;

			while (cur_node != nullptr)
			{
				nodes_position_list.push_back(cur_node->body_part.getPosition());
				cur_node = cur_node->next;
			}

			return nodes_position_list;
		}
		void SingleLinkedList::updateNodeDirection(Direction direction_to_set)
		{
			Node* cur_node = head_node;

			while (cur_node != nullptr)
			{
				Direction previous_direction = cur_node->body_part.getDirection();
				cur_node->body_part.setDirection(direction_to_set);
				direction_to_set = previous_direction;
				cur_node = cur_node->next;
			}
		}
		void SingleLinkedList::updateNodePosition()
		{
			Node* cur_node = head_node;

			while (cur_node != nullptr)
			{
				cur_node->body_part.updatePosition();
				cur_node = cur_node->next;
			}
		}
		
		void SingleLinkedList::insertNodeAtIndex(int index)
		{
			if (index < 0 || index >= linked_list_size) return;
			if (index == 0)
			{
				insertNodeAtHead();
				return;
			}
			Node* new_node = createNode();

			int current_index = 0;
			Node* cur_node = head_node;
			Node* prev_node = nullptr;

			while (cur_node != nullptr && current_index < index)
			{
				prev_node = cur_node;
				cur_node = cur_node->next;
				current_index++;
			}
			prev_node->next = new_node;
			new_node->next = cur_node;
			initializeNode(new_node, prev_node, Operation::TAIL);

			linked_list_size++;
			shiftNodesAfterInsertion(new_node, cur_node, prev_node);


		}*/
		/*int SingleLinkedList::findMiddleNode()
		{
			Node* fast_node = head_node;
			Node* slow_node = head_node;
			int middleindex = 0;


			while (fast_node != nullptr && fast_node->next != nullptr)
			{
				slow_node = slow_node->next;
				fast_node = fast_node->next->next;
				middleindex++;
			}
			return middleindex;
		}*/
		
		void SingleLinkedList::shiftNodesAfterRemoval(Node* cur_node)
		{
			sf::Vector2i prev_position = cur_node->body_part.getPosition();
			Direction prev_direction = cur_node->body_part.getDirection();

			cur_node = cur_node->next;

			while (cur_node != nullptr)
			{
				sf::Vector2i temp_position = cur_node->body_part.getPosition();
				Direction temp_direction = cur_node->body_part.getDirection();

				cur_node->body_part.setPosition(prev_position);
				cur_node->body_part.setDirection(prev_direction);

				cur_node = cur_node->next;
				prev_position = temp_position;
				prev_direction = temp_direction;
			}
		}
		/*Node* SingleLinkedList::getHeadNode()
		{
			return  head_node;
		}*/
		
	}
}

