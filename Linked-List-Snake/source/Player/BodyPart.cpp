#include "Player/BodyPart.h"
#include "Level/LevelView.h"


namespace Player {
	using namespace Global;
	using namespace Level;
	
	BodyPart::BodyPart()
	{
		createBodyPartImage();
	}

	BodyPart::~BodyPart()
	{
		destroy();
	}

	void BodyPart::initialize(float width, float height, sf::Vector2i pos, Direction dir)
	{
		bodypart_width = width;
		bodypart_height = height;
		direction = dir;
		grid_position = pos;

		
		initializeBodyPartImage();
	}
	void BodyPart::update()
	{

	}
	void BodyPart::render()
	{
		bodypart_image->render();
	}
	void BodyPart::destroy()
	{
		delete(bodypart_image);
	}
	void BodyPart::createBodyPartImage()
	{
		bodypart_image = new UI::UIElement::ImageView;
	}
	void BodyPart::initializeBodyPartImage()
	{
		bodypart_image->initialize(Config::snake_body_texture_path, bodypart_width, bodypart_height, getBodyPartScreenPosition());
		bodypart_image->setOriginAtCentre();
	}
	sf::Vector2f BodyPart::getBodyPartScreenPosition()
	{
		float x_screen_position = LevelView::border_offset_left + (grid_position.x * bodypart_width) + (bodypart_width / 2);
		float y_screen_position = LevelView::border_offset_top + (grid_position.y * bodypart_height) + (bodypart_height / 2);
		return sf::Vector2f(grid_position.x,grid_position.y);
	}

	void BodyPart::setDirection(Direction direction)
	{
		this->direction = direction;
	}

	Direction BodyPart::getDirection()
	{
		return direction;
	}

	sf::Vector2i BodyPart::getPosition()
	{
		return sf::Vector2i(grid_position);
	}

	float BodyPart::getRotationAngle()
	{
		switch (direction)
		{
		case Player::Direction::UP:
			return 270.0f;
			break;
		case Player::Direction::DOWN:
			return 180.0f;
			break;
		case Player::Direction::LEFT:
			return 90.0f;
			break;
		case Player::Direction::RIGHT:
			return 0.0f;
			break;
		}
	}

	void BodyPart::updatePosition()
	{
		bodypart_image->setPosition(getBodyPartScreenPosition());
		bodypart_image->setRotation(getRotationAngle());
		bodypart_image->update();
	}

	sf::Vector2i BodyPart::getNextPosition()
	{
		switch (direction)
		{
		case Player::Direction::UP:
			return getNextPositionUp();
			break;
		case Player::Direction::DOWN:
			return getNextPositionDown();
			break;
		case Player::Direction::LEFT:
			return getNextPositionLeft();
			break;
		case Player::Direction::RIGHT:
			return getNextPositionRight();
			break;
		default:
			return grid_position;
			break;
		}
	}
	sf::Vector2i BodyPart::getNextPositionUp()
	{
		return sf::Vector2i(grid_position.x, grid_position.y - 1);
	}

	sf::Vector2i BodyPart::getNextPositionDown()
	{
		return sf::Vector2i(grid_position.x, grid_position.y + 1);
	}

	void BodyPart::setPosition(sf::Vector2i position)
	{
		grid_position = position;
	}

	sf::Vector2i BodyPart::getNextPositionLeft()
	{
		return sf::Vector2i(grid_position.x - 1, grid_position.y);
	}

	sf::Vector2i BodyPart::getNextPositionRight()
	{
		return sf::Vector2i(grid_position.x + 1, grid_position.y);
	}	
}

