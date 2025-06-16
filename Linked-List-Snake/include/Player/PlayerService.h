#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
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
		float getCellWidth();

		std::vector<sf::Vector2i>getCurrentSnakePositionList();
	};
}