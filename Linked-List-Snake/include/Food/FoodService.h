#pragma once
#include "Food/FoodItem.h"
#include <random>
namespace Food {
	class FoodService {
	private:
		FoodItem* current_food_item;
		float cell_width;
		float cell_height;
		FoodItem* createFood(sf::Vector2i position, FoodType type);

		std::default_random_engine random_engine;
		std::random_device random_device;
		void spawnFood();
		void destroyFood();
		void reset();
	public:
		FoodService();
		~FoodService();

		void initialize();
		void update();
		void render();

		void startFoodSpawning();

		sf::Vector2i getRandomPosition();

		bool isValidPosition(std::vector<sf::Vector2i> position_data, sf::Vector2i food_position);

		sf::Vector2i getVaildSpawnPosition();

		FoodType getRandomFoodType();
	};
}