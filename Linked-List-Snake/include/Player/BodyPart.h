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

		float bodypart_width;
		float bodypart_height;

		Direction previous_direction;

		float getRotationAngle();
		

		sf::Vector2i getNextPosition();
		sf::Vector2i getNextPositionLeft();
		sf::Vector2i getNextPositionRight();
		sf::Vector2i getNextPositionUp();
		sf::Vector2i getNextPositionDown();
		void setPosition(sf::Vector2i position);

	public:
		BodyPart();
		~BodyPart();

		void initialize(float width, float height, sf::Vector2i pos, Direction dir);
		void update();
		void render();
		void destroy();

		void createBodyPartImage();
		void initializeBodyPartImage();
		sf::Vector2f getBodyPartScreenPosition();
		void setDirection(Direction direction);
		Direction getDirection();
		sf::Vector2i getPosition();
		void updatePosition();
	};
}
