#include "UI/LevelSelectionScreen/LevelSelectionUIController.h"
#include "Main/GameService.h"
#include "Graphics/GraphicService.h"
#include "Sound/SoundService.h"
#include "Event/EventService.h"
#include "Global/Config.h"

namespace UI
{
	namespace LevelSelection {
		using namespace Global;
		using namespace Event;
		using namespace Sound;
		using namespace Main;
		using namespace Graphics;
		using namespace UIElement;

		LevelSelectionUIController::LevelSelectionUIController()
		{
			createImage();
			createButtons();
		}
		LevelSelectionUIController::~LevelSelectionUIController()
		{
			destroy();
		}
		void LevelSelectionUIController::initialize()
		{
			initializeBackgroundImage();
			initializeButtons();
		}
		void LevelSelectionUIController::update()
		{
			background_image->update();
			level_one_button->update();
			level_two_button->update();
			menu_button->update();
		}
		void LevelSelectionUIController::render()
		{
			background_image->render();
			level_one_button->render();
			level_two_button->render();
			menu_button->render();
		}
		void LevelSelectionUIController::show()
		{
			background_image->show();
			level_one_button->show();
			level_two_button->show();
			menu_button->show();
		}
		void LevelSelectionUIController::createImage()
		{
			background_image = new ImageView();
		}
		void LevelSelectionUIController::createButtons()
		{
			level_one_button = new ButtonView();
			level_two_button = new ButtonView();
			menu_button = new ButtonView();
		}
		void LevelSelectionUIController::initializeBackgroundImage()
		{
			sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

			background_image->initialize(Config::background_texture_path, game_window->getSize().x, game_window->getSize().y, sf::Vector2f(0, 0));
			background_image->setImageAlpha(background_alpha);
		}
		void LevelSelectionUIController::initializeButtons()
		{
			level_one_button->initialize("Singly Linked List", Config::level_one_button_texture_path, button_width, button_height, sf::Vector2f(0, level_one_button_y_position));
			level_two_button->initialize("Doubly Linked List", Config::level_two_button_texture_path, button_width, button_height, sf::Vector2f(0, level_two_button_y_position));
			menu_button->initialize("Menu", Config::menu_button_texture_path, button_width, button_height, sf::Vector2f(0, menu_button_y_position));

			level_one_button->setCentreAlinged();
			level_two_button->setCentreAlinged();
			menu_button->setCentreAlinged();
		}
		void LevelSelectionUIController::destroy()
		{
			delete(level_one_button);
			delete(level_two_button);
			delete(menu_button);
			delete(background_image);
		}
	}
}
