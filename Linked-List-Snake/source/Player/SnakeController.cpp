#include "Player/SnakeController.h"

namespace Player {
	SnakeController::SnakeController()
	{

	}
	SnakeController::~SnakeController()
	{
		destory();
	}
	void SnakeController::initialize()
	{
	}
	void SnakeController::update()
	{
	}
	void SnakeController::render()
	{
	}
	void SnakeController::spawnSnake()
	{
	}
	void SnakeController::respawnSnake()
	{
	}
	void SnakeController::setSnakeState(SnakeState state)
	{
		current_snake_state = state;
	}
	SnakeState SnakeController::getSnakeState()
	{
		return current_snake_state;
	}
	void SnakeController::processPlayerInput()
	{
	}
	void SnakeController::updateSnakeDirection()
	{
	}
	void SnakeController::moveSnake()
	{
	}
	void SnakeController::processSnakeCollision()
	{
	}
	void SnakeController::handleRestart()
	{
	}
	void SnakeController::reset()
	{
	}
	void SnakeController::destory()
	{
		
	}
}

