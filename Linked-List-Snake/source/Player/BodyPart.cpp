#include "Player/BodyPart.h"


namespace Player {
	using namespace Global;
	
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
		return sf::Vector2f(grid_position.x,grid_position.y);
	}
	
}

