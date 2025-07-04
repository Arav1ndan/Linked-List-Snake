#include "Food/FoodService.h"
#include "Global/ServiceLocator.h"
#include "Food/FoodItem.h"
#include "Level/LevelModel.h"
#include "Player/PlayerService.h"

namespace Food
{
	using namespace Time;
	using namespace Global;
	using namespace Level;
	using namespace Player;
	using namespace LinkedList;

	FoodService::FoodService() : random_engine(random_device())
	{
		current_food_item = nullptr;
	}

	FoodService::~FoodService()
	{
		destroyFood();
	}

	void FoodService::initialize()
	{
		elapsed_duration = spawn_duration;		
	}

	void FoodService::update()
	{
		if (current_spawning_status == FoodSpawningStatus::ACTIVE)
		{
			updateElapsedDuration();
			handleFoodSpawning();
		}

		if (current_food_item)current_food_item->update();
	}

	void FoodService::render()
	{
		if (current_food_item)current_food_item->render();
	}
	void FoodService::spawningFood()
	{
		cell_width = ServiceLocator::getInstance()->getLevelService()->getCellWidth();
		cell_height = ServiceLocator::getInstance()->getLevelService()->getCellHeight();

		spawnFood();
	}
	void FoodService::handleFoodSpawning()
	{
		if (elapsed_duration >= spawn_duration)
		{
			destroyFood();
			reset();
			spawnFood();
		}
	}
	void FoodService::startFoodSpawning()
	{
		current_spawning_status = FoodSpawningStatus::ACTIVE;

		cell_width = ServiceLocator::getInstance()->getLevelService()->getCellWidth();
		cell_height = ServiceLocator::getInstance()->getLevelService()->getCellHeight();
		//spawnFood();
	}

	void FoodService::stopFoodSpawning()
	{
		current_spawning_status = FoodSpawningStatus::IN_ACTIVE;
		destroyFood();
		reset();
	}

	bool FoodService::processFoodCollision(Node* head_node, FoodType& out_food_type)
	{
		if (current_food_item && current_food_item->getFoodPosition() == head_node->body_part.getPosition())
		{
			out_food_type = current_food_item->getFoodType();
			return true;
		}
		return false;
	}

	FoodItem* FoodService::createFood(sf::Vector2i position, FoodType type)
	{
		FoodItem* food = new FoodItem();
		food->initialize(position, cell_width, cell_height, type);
		return food;
	}

	void FoodService::spawnFood()
	{
		//current_food_item = createFood(sf::Vector2i(4, 6), FoodType::ALCOHOL);
		current_food_item = createFood(getValidSpawnPosition(), getRandomFoodType());
	}

	sf::Vector2i FoodService::getValidSpawnPosition()
	{
		std::vector<sf::Vector2i> player_position_data = ServiceLocator::getInstance()->getPlayerService()->getCurrentSnakePositionList();
		std::vector<sf::Vector2i> elements_position_data = ServiceLocator::getInstance()->getElementService()->getElementPositionList();
		sf::Vector2i spawn_position;

		do spawn_position = getRandomPosition();
		while (!isValidPosition(player_position_data, spawn_position) || !isValidPosition(elements_position_data, spawn_position));

		return spawn_position;
	}

	sf::Vector2i FoodService::getRandomPosition()
	{
		// Co-ordinate distribution i.e. selecting random position for food.
		std::uniform_int_distribution<int> x_distribution(0, LevelModel::number_of_colums - 1);
		std::uniform_int_distribution<int> y_distribution(0, LevelModel::number_of_rows - 1);

		int x_position = static_cast<int>(x_distribution(random_engine));
		int y_position = static_cast<int>(y_distribution(random_engine));

		return sf::Vector2i(x_position, y_position);
	}

	FoodType FoodService::getRandomFoodType()
	{
		std::uniform_int_distribution<int> distribution(0, FoodItem::number_of_foods - 1);

		return static_cast<FoodType>(distribution(random_engine));
	}

	bool FoodService::isValidPosition(std::vector<sf::Vector2i> position_data, sf::Vector2i food_position)
	{
		for (int i = 0; i < position_data.size(); i++)
		{
			if (food_position == position_data[i]) return false;
		}
		return true;
	}

	void FoodService::destroyFood()
	{
		if (current_food_item) delete(current_food_item);
		current_food_item = nullptr;
	}

	void FoodService::updateElapsedDuration()
	{
		elapsed_duration += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
	}

	

	void FoodService::reset()
	{
		elapsed_duration = 0.f;
	}
}