#include "Player/SnakeController.h"
#include "Level/LevelService.h"
#include "Global/ServiceLocator.h"
#include "Event/EventService.h"
#include "Elements/ElementService.h"

namespace Player {
	using namespace LinkedList;
	using namespace Global;
	using namespace Level;
	using namespace Event;

	SnakeController::SnakeController()
	{
		single_linked_list = nullptr;
		createLinkedList();
		current_snake_direction = default_direction;
	}
	SnakeController::~SnakeController()
	{
		destory();
	}
	void SnakeController::createLinkedList()
	{
		single_linked_list = new SingleLinkedList();
	}
	void SnakeController::initialize()
	{
		float width =  ServiceLocator::getInstance()->getLevelService()->getCellWidth();
		float height = ServiceLocator::getInstance()->getLevelService()->getCellHeight();

		single_linked_list->initialize(width, height, default_position, default_direction);

		spawnSnake();
		//reset();
	} 
	
	void SnakeController::update()
	{
		switch (current_snake_state)
		{
		case Player::SnakeState::ALIVE:
			processPlayerInput();
			//updateSnakeDirection();
			//processSnakeCollision();
			delayedUpdate();
			//moveSnake();
			break;	
		case Player::SnakeState::DEAD:
			handleRestart();
			//respawnSnake();
			break;
		}
	}
	void SnakeController::render()
	{
		single_linked_list->render();
	}
	void SnakeController::spawnSnake()
	{
		

		for (int i = 0; i < initial_snake_length;i++) {
			single_linked_list->insertNodeAtTail();
		}
		
	}
	void SnakeController::respawnSnake()
	{
		single_linked_list->removeAllNodes();
		reset();
		spawnSnake();
	}
	void SnakeController::setSnakeState(SnakeState state)
	{
		current_snake_state = state;
	}
	SnakeState SnakeController::getSnakeState()
	{
		return current_snake_state;
	}

	std::vector<sf::Vector2i> SnakeController::getCurrentSnakePositionList()
	{
		return single_linked_list->getNodesPositionList();
	}

	void SnakeController::delayedUpdate()
	{
		processPlayerInput();


		elapsed_duration += Global::ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (elapsed_duration >= movement_frame_duration)
		{
			elapsed_duration = 0.f;
			updateSnakeDirection();
			processSnakeCollision();
			if (current_snake_state == SnakeState::ALIVE) {
				moveSnake();
			}
			inputState = InputState::WAITING;
		}
	}
	
	void SnakeController::processPlayerInput()
	{
		if (inputState == InputState::PROCESSING)
			return;

		Event::EventService* event_service = ServiceLocator::getInstance()->getEventService();

		if (event_service->pressedUpArrowKey() && current_snake_direction != Direction::DOWN)
		{
			current_snake_direction = Direction::UP;
			inputState = InputState::PROCESSING;
		}
		else if (event_service->pressedDownArrowKey() && current_snake_direction != Direction::UP)
		{
			current_snake_direction = Direction::DOWN;
			inputState = InputState::PROCESSING;
		}
		else if (event_service->pressedLeftArrowKey() && current_snake_direction != Direction::RIGHT)
		{
			current_snake_direction = Direction::LEFT;
			inputState = InputState::PROCESSING;
		}
		else if (event_service->pressedRightArrowKey() && current_snake_direction != Direction::LEFT)
		{
			current_snake_direction = Direction::RIGHT;
			inputState = InputState::PROCESSING;
		}
	}
	void SnakeController::updateSnakeDirection()
	{

		single_linked_list->updateNodeDirection(current_snake_direction); // current_node_direction
	}
	void SnakeController::moveSnake()
	{
		single_linked_list->updateNodePosition();
	}
	void SnakeController::processSnakeCollision()
	{
		processBodyCollision();
		processElementsCollision();
		processFoodCollision();
	}
	void SnakeController::handleRestart()
	{
		restart_counter += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (restart_counter >= restart_duration) {
			respawnSnake();
		}
	}
	void SnakeController::reset()
	{
		current_snake_state = SnakeState::ALIVE;
		current_snake_direction = default_direction;
		elapsed_duration = 0.0f;
		restart_counter = 0.0f;

		inputState = InputState::WAITING;
	}
	void SnakeController::destory()
	{
		delete(single_linked_list);
	}
	void SnakeController::processBodyCollision()
	{
		if (single_linked_list->processNodeCollision())
		{
			current_snake_state = SnakeState::DEAD;
			ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::DEATH);
		}
	}
	void SnakeController::processElementsCollision()
	{
		Element::ElementService* element_service = ServiceLocator::getInstance()->getElementService();

		if (element_service->processElementsCollision(single_linked_list->getHeadNode()))
		{
			current_snake_state = SnakeState::DEAD;
			ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::DEATH);
		}
	}
	void SnakeController::processFoodCollision()
	{
	}
}

