#include "../../include/Level/LevelService.h"
#include "../../include/Level/LevelController.h"
#include "Global/ServiceLocator.h"
#include "Elements/ElementData.h"

namespace Level
{
	using namespace Global;

	LevelService::LevelService()
	{
		level_controller = nullptr;
		//level_controller = new LevelController();


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

	void LevelService::spawnFood()
	{
		ServiceLocator::getInstance()->getFoodService()->startFoodSpawning();
	}

	void LevelService::createLevel(LevelNumber level_to_load)
	{
		current_level = level_to_load;
		spawnLevelElements(level_to_load);
		spawnFood();
		spawnPlayer();
		
	}

	void LevelService::spawnLevelElements(LevelNumber level_to_load)
	{
		float cell_width = level_controller->getCellWidth();
		float cell_height = level_controller->getCellHeight();

		std::vector<Element::ElementData> elemetDataList = level_controller->getElementDataList((int)level_to_load);
		ServiceLocator::getInstance()->getElementService()->spawnElements(elemetDataList, cell_width, cell_height);
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