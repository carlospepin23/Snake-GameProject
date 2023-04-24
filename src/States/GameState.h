#pragma once

#include "State.h"
#include "Snake.h"
#include "StaticEntity.h"
#include "ofMain.h"

class GameState : public State {
    public:
        GameState();
        ~GameState();
        void reset();
        void update();
        void draw();
        void keyPressed(int key);
        void foodSpawner();
        void powUpManager(int score);
        void drawFood();
        void entitiesSpawner();
        void drawEntities();
        // void drawStartScreen();
        // void drawLostScreen();
        void drawBoardGrid();

        Snake* snake;

        //Entities
        vector<StaticEntity> entities;

        int cellSize; // Pixels

        bool foodSpawned = false;
        bool powUpSpawned = false;

        int currentFoodX;
        int currentFoodY;

        int boardSizeWidth, boardSizeHeight;
        

        int score = 0;
        bool power_up_first=false,power_up_second=false,power_up_third=false,power_up_activated=false;
        
        string pow_up_s="None";
        unsigned int pow_up=0;

        bool entitySpawned = false;
};