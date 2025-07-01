#pragma once
#include "Player/Direction.h"
#include "UI/UIElement/ImageView.h"
#include "Global/Config.h"
#include <SFML/Graphics.hpp>

namespace Player {
	class BodyPart {
	protected:
		UI::UIElement::ImageView* bodypart_image;

		sf::Vector2i grid_position;
		Direction direction;
		Direction previous_direction;

		float bodypart_width;
		float bodypart_height;

		void createBodyPartImage();
		void initializeBodyPartImage();
		sf::Vector2f getBodyPartScreenPosition();

		float getRotationAngle();
		

		
		sf::Vector2i getNextPositionLeft();
		sf::Vector2i getNextPositionRight();
		sf::Vector2i getNextPositionUp();
		sf::Vector2i getNextPositionDown();
		//void setPosition(sf::Vector2i position);


		void destroy();
	public:
		BodyPart();
		~BodyPart();

		void initialize(float width, float height, sf::Vector2i pos, Direction dir);
		void render();
		
		void setDirection(Direction direction);
		Direction getDirection();
		Direction getPrevDirection();
		

		void setPosition(sf::Vector2i position);
		sf::Vector2i getPosition();		
		sf::Vector2i getNextPosition();

		void updatePosition();
		sf::Vector2i getPrevPosition();
	};
}
