#pragma once
#include "../../include/Level/LevelService.h"
#include "../../include/Level/LevelNumber.h"

namespace Level
{
	struct LevelData
	{
		LevelData(LevelNumber ind) 
		{
			level_index = ind;
		}

		LevelNumber level_index;
	};
}