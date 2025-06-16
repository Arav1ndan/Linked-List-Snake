#pragma once
#include <SFML/Graphics.hpp>
#include "Level/LevelData.h"
#include "Elements/ElementService.h"
#include "Elements/ElementData.h"
#include <vector>

namespace Level {
	class LevelModel {
	private:
		std::vector<LevelData> level_configuration;

		std::vector<Element::ElementData> level_one_element_list;
		std::vector<Element::ElementData> level_two_element_list;

		float cell_width;
		float cell_height;

		void initializeLevelData();
	public:
		static const int number_of_rows = 28;
		static const int number_of_colums = 50;

		LevelModel();
		~LevelModel();
		void initialize(int width, int height);
		float getCellWidth();
		float getCellHeight();

		const std::vector<Element::ElementData>& getElementDataList(int levelToLoad);
	};
}