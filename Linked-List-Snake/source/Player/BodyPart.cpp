#include "Player/BodyPart.h"
#include "Level/LevelView.h"
#include "Level/LevelModel.h"


namespace Player {
	using namespace Global;
	using namespace Level;
	
	BodyPart::BodyPart()
	{
		grid_position = sf::Vector2i(0, 0);

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
		float y_screen_position = LevelView::border_offset_top + (grid_position.y * bodypart_height) +(bodypart_height / 2);

		return sf::Vector2f(x_screen_position, y_screen_position);
	}



	Direction BodyPart::getDirection()
	{
		return direction;
	}
	Direction BodyPart::getPrevDirection()
	{
		return previous_direction;
	}

	void BodyPart::setDirection(Direction direction)
	{
		previous_direction = this->direction;

		this->direction = direction;
	}

	void BodyPart::setPosition(sf::Vector2i position)
	{
		grid_position = position;
	}
	sf::Vector2i BodyPart::getPosition()
	{
		return grid_position;
	}

	float BodyPart::getRotationAngle()
	{
		switch (direction)
		{
		case Player::Direction::UP:
			return 270.0f;
			break;
		case Player::Direction::DOWN:
			return 90.0f; //180.0f; //90
			break;
		case Player::Direction::LEFT:
			return 180.0f; //90.0f; //180
			break;
		case Player::Direction::RIGHT:
			return 0.0f;
			break;
		}
	}
	void BodyPart::updatePosition()
	{
		grid_position = getNextPosition();

		sf::Vector2f screenPosition = getBodyPartScreenPosition();

		bodypart_image->setPosition(screenPosition);
		bodypart_image->setRotation(getRotationAngle());
		bodypart_image->update();
	}

	sf::Vector2i BodyPart::getPrevPosition()
	{
		switch (direction)
		{
		case Player::Direction::UP:
			return getNextPositionDown();
			
		case Player::Direction::DOWN:
			return getNextPositionUp();
		
		case Player::Direction::LEFT:
			return getNextPositionRight();
	
		case Player::Direction::RIGHT:
			return getNextPositionLeft();
	
		default:
			return grid_position;
		}
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
		return sf::Vector2i(grid_position.x, (grid_position.y - 1 + (LevelModel::number_of_rows)) % (LevelModel::number_of_rows));
	}

	sf::Vector2i BodyPart::getNextPositionDown()
	{
		return sf::Vector2i(grid_position.x, (grid_position.y + 1) % (LevelModel::number_of_rows));
	}

	
	sf::Vector2i BodyPart::getNextPositionLeft()
	{
		return sf::Vector2i((grid_position.x - 1 + LevelModel::number_of_colums) % (LevelModel::number_of_colums), grid_position.y);
	}

	sf::Vector2i BodyPart::getNextPositionRight()
	{
		return sf::Vector2i((grid_position.x + 1) % (LevelModel::number_of_colums), grid_position.y);
	}	
}

