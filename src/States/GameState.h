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
        // void speedBoostManager();
        void powUpDisplay(int p_score);
        void drawFood();
        void entitiesSpawner();
        void drawEntities();
        // void drawStartScreen();
        // void drawLostScreen();
        void drawBoardGrid();
        void mousePressed(int x, int y, int button);
        void tick();

        int getScore(){return this->last_score;}

        Snake* snake;

        //Entities
        vector<StaticEntity> entities;

        int cellSize; // Pixels

        bool foodSpawned = false;

        int currentFoodX;
        int currentFoodY;

        int boardSizeWidth, boardSizeHeight;
        int last_score=0;
        int score = 0;
        bool entitySpawned = false;
        int p_score=0;
        bool powUp_Better_Apple=false, powUp_Speed_Boost=false, powUp_PacMan_Mode=false;
        string pow_up_s="None";
        unsigned int pow_up=0;
        int ticks=0;
        int seconds=0;
        int timer=0;

        int green = 0;
        int red = 255;

        int decayCounter = 0;

        int foodTimer = 30;

        int previousDecayCounter = 0;


        void rockSpawner() {
            entities.push_back(StaticEntity("rock",ofColor::gray,ofRandom(1, (boardSizeWidth-1)), ofRandom(1, (boardSizeHeight-2)),25));
            entitySpawned=true;
        }

        void treeSpawner() {
            int trunkX=ofRandom(1, (boardSizeWidth-1));
            int trunkY=ofRandom(1, (boardSizeHeight-2));
            entities.push_back(StaticEntity("trunk", ofColor::brown, trunkX, trunkY, 25));
            entities.push_back(StaticEntity("trunk",ofColor::brown,trunkX, trunkY+1, 25));  // creates 2 trunks

            int leavesX = trunkX;
            int leavesY = trunkY - 1;
            entities.push_back(StaticEntity("leaves", ofColor::green, leavesX, leavesY, 25));

            leavesX = trunkX - 1;
            leavesY = trunkY;
            entities.push_back(StaticEntity("leaves", ofColor::green, leavesX, leavesY, 25));  // adds the leaves. 1 on top, 1 on each side, total 3

            leavesX = trunkX + 1;
            leavesY = trunkY;
            entities.push_back(StaticEntity("leaves", ofColor::green, leavesX, leavesY, 25));
        }

        void waterSpawner() {
            int water2X = ofRandom(1, (boardSizeWidth-1));
            int water2Y = ofRandom(1, (boardSizeHeight-2));
            entities.push_back(StaticEntity("water", ofColor::blue, water2X, water2Y, 25));
            entities.push_back(StaticEntity("water", ofColor::blue, water2X, water2Y+1, 25));   // a 4x4 puddle of water
            entities.push_back(StaticEntity("water", ofColor::blue, water2X+1, water2Y, 25));
            entities.push_back(StaticEntity("water", ofColor::blue, water2X+1, water2Y+1, 25));
        }
};