#pragma once
#include <SFML/Graphics.hpp>
#include "Player/Direction.h"
#include "LinkedListLib/SingleLinked/SingleLinkedList.h"
#include "LinkedListLib/Node.h"
#include "Food/FoodType.h"

namespace Player {
	using namespace LinkedListLib;
	enum class TimeComplexity
	{
		NONE,
		ONE,
		N,
	};

	enum class LinkedListOperations
	{
		NONE,
		INSERT_AT_HEAD,
		INSERT_AT_TAIL,
		INSERT_AT_MID,
		REMOVE_AT_HEAD,
		REMOVE_AT_TAIL,
		REMOVE_AT_MID,
		DELETE_HALF_LIST,
		REVERSE_LIST,
	};
	enum class SnakeState {
		ALIVE,
		DEAD,
	};
	enum class InputState {
		WAITING,
		PROCESSING
	};
	class SnakeController {
	private:

		LinkedListLib::LinkedList* linked_list;
		

		const int initial_snake_length = 10;

		const sf::Vector2i default_position = sf::Vector2i(25, 13);
		const Direction default_direction = Direction::RIGHT;

		const float movement_frame_duration = 0.1f;

		float elapsed_duration;
		

		SnakeState current_snake_state;
		Direction current_snake_direction;

		InputState inputState;
		

		const float restart_duration = 2.f;
		float restart_counter;


		TimeComplexity time_complexity;
		LinkedListOperations last_linked_list_operation;
		void processPlayerInput();
		void updateSnakeDirection();
		void moveSnake();
		void processSnakeCollision();
		void handleRestart();
		void reset();
		void destory();

		void processBodyCollision();
		void processElementsCollision();
		void processFoodCollision();


		int player_score = 0;

	public:
		SnakeController();
		~SnakeController();


		void createLinkedList(LinkedListType level_type);


		void initializeLinkedList();
		void initialize();
		void update();
		void render();

		void spawnSnake();
		void respawnSnake();
		void setSnakeState(SnakeState state);
		SnakeState getSnakeState();

		std::vector<sf::Vector2i> getCurrentSnakePositionList();

		void OnFoodCollected(Food::FoodType food_type);

		void delayedUpdate();
		
		int getPlayerScore();

		TimeComplexity getTimeComplexity();
		LinkedListOperations getLastOperation();

		bool isSnakeDead();
		
	};
}