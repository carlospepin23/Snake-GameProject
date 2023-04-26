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
        void powUpDisplay(int p_score);
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

        int currentFoodX;
        int currentFoodY;

        int boardSizeWidth, boardSizeHeight;
        

        int score = 0;
        bool entitySpawned = false;

        int p_score=0;
        bool powUp_Better_Apple=false;
        string pow_up_s="None";
        unsigned int pow_up=0;



};