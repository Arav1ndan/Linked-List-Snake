#pragma once
#include <SFML/Graphics.hpp>
#include "UI/Interface/IUIController.h"
#include "UI/UIElement/ImageView.h"
#include "UI/UIElement/ButtonView.h"

namespace UI
{
	namespace LinkedListSelection
	{
		class LinkedListSelectionScreen : public Interface::IUIController
		{
		private:
			const float button_width = 400.f;
			const float button_height = 140.f;

			const float single_button_y_position = 500.f;
			const float double_button_y_position = 700.f;
			const float menu_button_y_position = 900.f;

			const float background_alpha = 85.f;

			UIElement::ImageView* background_image;

			UIElement::ButtonView* single_button;
			UIElement::ButtonView* double_button;
			UIElement::ButtonView* menu_button;

			void createImage();
			void createButtons();
			void initializeBackgroundImage();
			void initializeButtons();
			void registerButtonCallback();

			void singleLinkedListCallback();
			void doubleLinkedListCallback();
			void menuButtonCallback();

			void destroy();
		public:
			LinkedListSelectionScreen();
			~LinkedListSelectionScreen();

			void initialize() override;
			void update() override;
			void render() override;
			void show() override;
		};
	}
}