#pragma once
#include "../../include/Level/LevelNumber.h"


namespace Level {
	class LevelController;
	class LevelService {
    private:
        LevelController* level_controller;
        LevelNumber current_level;

        void createLevelController();
        void destroy();

        void spawnPlayer();

    public:
        LevelService();
        ~LevelService();

        void initialize();
        void update();
        void render();
        float getCellWidth();
        float getCellHeight();

        void spawnFood();

        void createLevel(LevelNumber level_to_load); 

        void spawnLevelElements(LevelNumber level_to_load);

        LevelNumber getCurrentLevel();

        void setCurrentLevelNumber(LevelNumber level_to_load);
	};
}
