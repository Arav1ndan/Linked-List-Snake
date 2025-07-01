#include "LinkedList/SingleLinkedList.h"
#include "Player/BodyPart.h"
#include "Level/LevelView.h"
#include <iostream>

namespace LinkedList {
	
	SingleLinkedList::SingleLinkedList()
	{
		head_node = nullptr;
	}

	SingleLinkedList::~SingleLinkedList() = default;	
	
	void SingleLinkedList::initialize(float width, float height, sf::Vector2i position, Player::Direction direction)
	{
		node_width = width;
		node_height = height;
		default_position = position;
		default_direction = direction;

		linked_list_size = 0;

	}
	void SingleLinkedList::initializeNode(Node* new_node, Node* reference_node, Operation operation)
	{
		if (reference_node == nullptr)
		{
			new_node->body_part.initialize(node_width, node_height, default_position, default_direction);
			return;
		}
		sf::Vector2i position = getNewNodePosition(reference_node, operation);

		new_node->body_part.initialize(node_width, node_height, position, reference_node->body_part.getDirection());
	}
	void SingleLinkedList::render()
	{
		Node* cur_node = head_node;

		while (cur_node != nullptr)
		{
			cur_node->body_part.render();
			cur_node = cur_node->next;
		}
		
	}

	
	
	Node* SingleLinkedList::createNode()
	{
		return new Node();
	}

	//void SingleLinkedList::createHeadNode()
	//{
	//	head_node = createNode();
	//	head_node->body_part.initialize(node_width, node_height, default_position, default_direction);
	//	return;
	//}
	//Node* SingleLinkedList::createNode()
	//{
	//	return new Node();
	//}
	sf::Vector2i SingleLinkedList::getNewNodePosition(Node* reference_node)
	{
		Direction reference_direction = reference_node->body_part.getDirection();
		sf::Vector2i referece_position = reference_node->body_part.getPosition();

		switch (reference_direction)
		{
		case Player::Direction::UP:
			return sf::Vector2i(referece_position.x, referece_position.y - 1);
			break;
		case Player::Direction::DOWN:
			return sf::Vector2i(referece_position.x, referece_position.y + 1);
			break;
		case Player::Direction::LEFT:
			return sf::Vector2i(referece_position.x + 1, referece_position.y);
			break;
		case Player::Direction::RIGHT:
			return sf::Vector2i(referece_position.x - 1, referece_position.y);
			break;
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

	sf::Vector2i SingleLinkedList::getNewNodePosition(Node* reference_node, Operation operation)
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
		

	}
	int SingleLinkedList::findMiddleNode()
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
	}
	void SingleLinkedList::insertNodeAtMiddle()
	{
		if (head_node == nullptr)
		{
			insertNodeAtHead();
			return;
		}
		int middle_index = findMiddleNode();
		insertNodeAtIndex(middle_index);
	}
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
	Node* SingleLinkedList::getHeadNode()
	{
		return  head_node;
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
}

