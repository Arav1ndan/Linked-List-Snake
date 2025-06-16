#pragma once
#include <SFML/Graphics.hpp>
#include "UI/UIElement/ImageView.h"
#include "Food/FoodType.h"
namespace Food {
	class FoodItem {
	private:
		UI::UIElement::ImageView* food_image;
		sf::Vector2i grid_position;
		float cell_width;
		float cell_height;
		FoodType food_type;

		void initializeFoodImage();
	public:
		static const int number_of_foods = 8;

		FoodItem();
		~FoodItem();

		void initialize(sf::Vector2i grid_pos, float width, float height, FoodType type);
		void update();
		void render();

		sf::String getFoodTexturePath();
		sf::Vector2f getFoodImagePosition();

		FoodType getFoodType();
		sf::Vector2i getFoodPosition();
	};
}