#include "UI/LinkedListSelectionScreen/LinkedListSelectionScreen.h"
#include "Main/GameService.h"
#include "Graphics/GraphicService.h"
#include "Sound/SoundService.h"
#include "Event/EventService.h"
#include "Global/Config.h"
#include "Global/ServiceLocator.h"

namespace UI
{
	namespace LinkedListSelection
	{
		using namespace Global;
		using namespace Main;
		using namespace UIElement;
		using namespace Sound;



		LinkedListSelectionScreen::LinkedListSelectionScreen()
		{
			createImage();
			createButtons();
		}

		LinkedListSelectionScreen::~LinkedListSelectionScreen()
		{
			destroy();
		}

		void LinkedListSelectionScreen::initialize()
		{
			initializeBackgroundImage();
			initializeButtons();
			registerButtonCallback();
		}

		void LinkedListSelectionScreen::createImage()
		{
			background_image = new ImageView();
		}

		void LinkedListSelectionScreen::createButtons()
		{
			single_button = new ButtonView();
			double_button = new ButtonView();
			menu_button = new ButtonView();
		}

		void LinkedListSelectionScreen::initializeBackgroundImage()
		{
			sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

			background_image->initialize(Config::background_texture_path, game_window->getSize().x, game_window->getSize().y, sf::Vector2f(0, 0));
			background_image->setImageAlpha(background_alpha);
		}

		void LinkedListSelectionScreen::initializeButtons()
		{
			single_button->initialize("Single Linked List", Config::single_linked_list_button_texture_path, button_width, button_height, sf::Vector2f(0, single_button_y_position));
			double_button->initialize("Double Linked List", Config::double_linked_list_button_texture_path, button_width, button_height, sf::Vector2f(0, double_button_y_position));
			menu_button->initialize("Menu Button", Config::menu_button_texture_path, button_width, button_height, sf::Vector2f(0, menu_button_y_position));

			single_button->setCentreAlinged();
			double_button->setCentreAlinged();
			menu_button->setCentreAlinged();
		}

		void LinkedListSelectionScreen::registerButtonCallback()
		{
			single_button->registerCallbackFuntion(std::bind(&LinkedListSelectionScreen::singleLinkedListCallback, this));
			double_button->registerCallbackFuntion(std::bind(&LinkedListSelectionScreen::doubleLinkedListCallback, this));
			menu_button->registerCallbackFuntion(std::bind(&LinkedListSelectionScreen::menuButtonCallback, this));
		}

		void LinkedListSelectionScreen::singleLinkedListCallback()
		{
		}

	}
} 
