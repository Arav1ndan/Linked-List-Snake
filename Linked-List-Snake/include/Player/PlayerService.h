#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player/SnakeController.h"
#include "Level/LevelNumber.h"
namespace Player {
	using namespace Level;
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

		void spawnPlayer(LinkedListType level_type);
		
		int getPlayerScore();
		std::vector<sf::Vector2i>getCurrentSnakePositionList();

		TimeComplexity getTimeComplexity();
		LinkedListOperations getLastOperation();
	};
}