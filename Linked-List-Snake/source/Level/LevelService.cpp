#include "../../include/Level/LevelService.h"
#include "../../include/Level/LevelController.h"
#include "Global/ServiceLocator.h"

namespace Level
{
	using namespace Global;

	LevelService::LevelService()
	{
		level_controller = nullptr;

		createLevelController();
	}

	LevelService::~LevelService()
	{
		destroy();
	}

	void LevelService::createLevelController()
	{
		level_controller = new LevelController();
	}

	void LevelService::initialize()
	{
		level_controller->initialize();
	}

	void LevelService::update()
	{
		level_controller->update();
	}	

	void LevelService::render()
	{
		level_controller->render();
	}

	float LevelService::getCellWidth()
	{
		return level_controller->getCellWidth(); 
	}

	float LevelService::getCellHeight()
	{
		return level_controller->getCellHeight();
	}

	void LevelService::createLevel(LevelNumber level_to_load)
	{
		current_level = level_to_load;
	}

	void LevelService::destroy()
	{
		delete level_controller;
	}
	void LevelService::spawnPlayer()
	{
		ServiceLocator::getInstance()->getLevelService()->spawnPlayer();
	}
	//void LevelService::getCellWidth()
	//{
		//return 
	//}
}