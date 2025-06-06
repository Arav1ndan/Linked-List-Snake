#pragma once
#include "LinkedList/Node.h"

namespace LinkedList {
	class SingleLinkedList{
	private:
		Node* head_node;
		float node_width;
		float node_height;
		sf::Vector2i default_position;
		Direction default_direction;

		Node* createNode();
		
	public:
		SingleLinkedList();
		~SingleLinkedList();

		void initialize(float width, float height, sf::Vector2i position, Direction direction);
		void render();

		void createHeadNode();

	};
}