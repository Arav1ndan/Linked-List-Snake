#include "../../include/Level/LevelModel.h"


namespace Level {


	LevelModel::LevelModel() = default;
	LevelModel::~LevelModel() = default;

	void LevelModel::initialize(int width, int height)
	{
		cell_width = static_cast<float>(width) / static_cast<float>(number_of_colums);
		cell_height = static_cast<float>(height) / static_cast<float>(number_of_rows);

		initializeLevelData();
	}
	void LevelModel::initializeLevelData()
	{
		level_configuration.push_back(LevelData(Level::LevelNumber::ONE, &level_one_element_list));

		level_configuration.push_back(LevelData(Level::LevelNumber::TWO, &level_two_element_list));
	}

	float LevelModel::getCellWidth()
	{
		return cell_width;
	}

	float LevelModel::getCellHeight()
	{
		return cell_height;
	}
	const std::vector<Element::ElementData>& LevelModel::getElementDataList(int level_to_load)
	{
		return *level_configuration[level_to_load].element_data_list; //stoped here while debugging.
	}


}
