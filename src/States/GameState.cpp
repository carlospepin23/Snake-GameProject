#include "GameState.h"

//--------------------------------------------------------------
GameState::GameState() {
    foodSpawned = false;
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
}
//--------------------------------------------------------------
GameState::~GameState() {
    delete snake;
    entities.clear();
}
//--------------------------------------------------------------
void GameState::reset() {
    delete snake;
    entities.clear();
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    foodSpawned = false;
    entitySpawned=false;
    setFinished(false);
    setNextState("");
}
//--------------------------------------------------------------
void GameState::update() {

    if(snake->isCrashed()) {
        this->setNextState("LoseState");
        this->setFinished(true);
        return;
    }

    if(snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY){
        if(powUp_Better_Apple==false) snake->grow();
        else{
            snake->grow();
            snake->grow();
            snake->grow();
            snake->grow();
        }
        foodSpawned = false;
    }
    powUpManager(this->p_score);
    foodSpawner();
    entitiesSpawner();

    for(int i=0;i<entities.size();i++){
        if(snake->getHead()[0] == entities[i].getEntityX() && snake->getHead()[1] == entities[i].getEntityY()){
            snake->setCrashed(true);
        }
    }

    if(ofGetFrameNum() % 10 == 0) {
        snake->update();
    }
    if (snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY) {
        score += 10;
        p_score=(p_score%150)+10;
    }
    if (snake->isCrashed()) {
        score = 0;
        p_score = 0;
        pow_up_activated=false;
        powUp_Better_Apple=false;
    }
}
//--------------------------------------------------------------
void GameState::draw() {
    drawBoardGrid();
    snake->draw();
    drawFood();
    drawEntities();
    ofDrawBitmapString("Score: " + ofToString(score), 10, 20);
    ofDrawBitmapString("Current Power_Up: " + pow_up_s, 10, 40);
}
//--------------------------------------------------------------
void GameState::keyPressed(int key) {

    if(key != OF_KEY_LEFT && key != OF_KEY_RIGHT && key != OF_KEY_UP && key != OF_KEY_DOWN && key !='a' && key!='u' && key!='b') { return; }

    switch(key) {
        case OF_KEY_LEFT:
            snake->changeDirection(LEFT);
            break;
        case OF_KEY_RIGHT:
            snake->changeDirection(RIGHT);
            break;
        case OF_KEY_UP:
            snake->changeDirection(UP);
            break;
        case OF_KEY_DOWN:
            snake->changeDirection(DOWN);
            break;
        case 'a':
            score+=10;
            p_score=(p_score%150)+10;
            break;
        case 'u':
            if(snake->getBody().size()>2) snake->removeSegment();
            break;
         case 'b':
            pow_up_activated=false; //Declarar el codigo de los powerups
            switch(pow_up){
                case 1:
                    //speedboost
                    break;
                case 2:
                    powUp_Better_Apple=true;
                    break;
                case 3:
                    //godmode
                    break;
            }
            break;
    }
}
//--------------------------------------------------------------
void GameState::foodSpawner() {
    if(!foodSpawned) {
        bool isInSnakeBody;
        do {
            isInSnakeBody = false;
            currentFoodX = ofRandom(1, boardSizeWidth-1);
            currentFoodY = ofRandom(1, boardSizeHeight-1);
            for(unsigned int i = 0; i < snake->getBody().size(); i++) {
                if(currentFoodX == snake->getBody()[i][0] and currentFoodY == snake->getBody()[i][1]){
                    isInSnakeBody = true;
                }
            }
        } while(isInSnakeBody);
        powUpDisplay(p_score);
        foodSpawned = true;
    }
}
//--------------------------------------------------------------
void GameState::drawFood() {
    if(foodSpawned){
        switch (pow_up){
            case 1:
                ofSetColor(ofColor::orange);
                ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
                break;
            case 2:
                ofSetColor(ofColor::green);
                ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
                break;
            case 3:
                ofSetColor(ofColor::white);
                ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
                break;
            default:
                ofSetColor(ofColor::red);
                ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
                break;
        }

    }
}
//--------------------------------------------------------------
void GameState::entitiesSpawner() { //method in charge of creating and adding entities
    if(!entitySpawned){
        entities.push_back(StaticEntity("rock",ofColor::gray,ofRandom(1, (boardSizeWidth-1)/2), ofRandom(1, (boardSizeHeight-1))/2,25));
        entitySpawned=true;
    }
}
//--------------------------------------------------------------
void GameState::drawEntities() { //method in charge of drawing all the entities
    if(entitySpawned){
        for(int i=0;i<entities.size();i++){
            entities[i].draw();
        }
    }

    
}

void GameState::drawBoardGrid() {
    
    ofDrawGrid(25, 64, false, false, false, true);
    
    // ofSetColor(ofColor::white);
    // for(int i = 0; i <= boardSize; i++) {
    //     ofDrawLine(i*cellSize, 0, i*cellSize, ofGetHeight());
    //     ofDrawLine(0, i*cellSize, ofGetWidth(), i*cellSize);
    // }
}
//--------------------------------------------------------------

void GameState::powUpManager(int p_score){
    //Spawner
    if(p_score==50) pow_up=1;
    else if(p_score==100 && powUp_Better_Apple==false)  pow_up=2;
    else if(p_score==150) pow_up=3;
    else pow_up=0;
    
}
//--------------------------------------------------------------

void GameState::powUpDisplay(int p_score){
    //Texto PowUps

    if (pow_up_activated==false && (p_score!=60) && p_score!=110 && p_score!=10 ) pow_up_s="None"; //corregir linea para que ponga el estado corriente, y si lo usa pona None.

    else if(p_score==60){
        pow_up_s="SpeedBoost";
        pow_up_activated=true;
    }
    else if (p_score==110){
        pow_up_s="BetterApple";
        pow_up_activated=true;
    }
    else if (p_score==10 && score!=0){
        pow_up_s="GodMode";
        pow_up_activated=true;
    }
}