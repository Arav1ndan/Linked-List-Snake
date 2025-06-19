#pragma once
#include <SFML/Graphics.hpp>
#include "../../include/Global/ServiceLocator.h"
#include "../../include/UI/UIElement/RectangleShapeView.h"

namespace Level {
	class RectangleShapeView;
	class LevelView {
	private:
		const sf::Color background_color = sf::Color(180, 200, 160);
		sf::Color border_color = sf::Color::Black;

		UI::UIElement::RectangleShapeView* background_rectangle;
		UI::UIElement::RectangleShapeView* border_rectangle;

		float grid_width;
		float grid_height;
		
		void createViews();
		void initializeBackground();
		void initializeBorder();
		void calculateGridExtents();
		void destroy();


		//RectangleShapeView* border_rectangle;
	public:
		static const int border_thickness = 10;
		static const int border_offset_left = 40;
		static const int border_offset_top = 40;

		LevelView(LevelController* controller);
		~LevelView();

		void initialize();
		void update();
		void render();

		float getGridWidth();
		float getGridHeight();
	};
}