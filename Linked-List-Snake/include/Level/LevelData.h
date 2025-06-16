#pragma once
#include "../../include/Level/LevelService.h"
#include "../../include/Level/LevelNumber.h"
#include "Elements/ElementData.h"

namespace Level
{
	struct LevelData
	{
		LevelData(LevelNumber ind, std::vector<Element::ElementData>* DataList) 
		{
			level_index = ind;
			element_data_list = DataList;
		}

		LevelNumber level_index;
		std::vector<Element::ElementData>* element_data_list;
	};
}