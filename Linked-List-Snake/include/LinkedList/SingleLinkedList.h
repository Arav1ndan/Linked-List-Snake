#pragma once
#include "LinkedList/Node.h"

namespace LinkedList {
	enum class Operation {
		HEAD,
		MID,
		TAIL
	};
	class SingleLinkedList{
	private:
		Node* head_node;
		float node_width;
		float node_height;
		sf::Vector2i default_position;
		Direction default_direction;

		Node* createNode();

		void initializeNode(Node* new_node, Node* reference_node, Operation operation);

		sf::Vector2i getNewNodePosition(Node* reference_node);
		
		int linked_list_size;

		void shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node);

	public:
		SingleLinkedList();
		~SingleLinkedList();

		void initialize(float width, float height, sf::Vector2i position, Player::Direction direction);
		void render();

		void insertNodeAtHead();
		void insertNodeAtTail();
		void insertNodeAtIndex(int index);
		void insertNodeAtMiddle();

		void removeAllNodes();
		void removeNodeAtHead();
		void removeNodeAtIndex(int index);
		void removeNodeAt(int index);
		void removeNodeAtMiddle();
		//void removeNodeAtTail();
		//void removeHalfNode();
		
		void shiftNodesAfterRemoval(Node* cur_node);

		Node* getHeadNode();

		std::vector<sf::Vector2i> getNodesPositionList();
		sf::Vector2i getNewNodePosition(Node* reference_node, Operation operation);
		
		void updateNodeDirection(Direction direction_to_set);
		void updateNodePosition();

		bool processNodeCollision();
		
		int findMiddleNode();

		void createHeadNode();
		
		
		

	};
}