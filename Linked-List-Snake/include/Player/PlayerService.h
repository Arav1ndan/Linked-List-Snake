#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player/SnakeController.h"
namespace Player {
	class SnakeController;
	class PlayerService {
	private:
		SnakeController* snake_controller;
		void createController();
		void destroy();
	public:

		PlayerService();
		~PlayerService();

		void initialize();
		void update();
		void render();

		void spawnPlayer();
		
		int getPlayerScore();
		std::vector<sf::Vector2i>getCurrentSnakePositionList();

		TimeComplexity getTimeComplexity();
		LinkedListOperations getLastOperation();
	};
}