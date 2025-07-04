#pragma once
#include <SFML/Graphics.hpp>

namespace Element
{
	enum class ElementType
	{
		OBSTACLE
	};

	struct ElementData
	{
		ElementData(ElementType type, sf::Vector2i pos)
		{
			element_type = type;
			position = pos;
		}

		ElementType element_type;
		sf::Vector2i position;
	};
}