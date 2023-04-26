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
    if (getNextState() == "PauseState") {
        setFinished(false);
        setNextState("");
        return;
    }
    else {
    delete snake;
    entities.clear();
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    foodSpawned = false;
    entitySpawned=false;
    setFinished(false);
    setNextState("");
    }
}
//--------------------------------------------------------------
void GameState::update() {

    if(snake->isCrashed()) {
        this->setNextState("LoseState");
        this->setFinished(true);
        return;
    }

    if(snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY) {
        snake->grow();
        foodSpawned = false;
    }

    foodSpawner();
    entitiesSpawner();

    for(unsigned int i=0;i<entities.size();i++){
        if(snake->getHead()[0] == entities[i].getEntityX() && snake->getHead()[1] == entities[i].getEntityY()){
            snake->setCrashed(true);
        }
    }




    if(ofGetFrameNum() % 10 == 0) {
        snake->update();
    }
    if (snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY) {
        score += 10;
    }
    if (snake->isCrashed()) {
        score = 0;
    }
}
//--------------------------------------------------------------
void GameState::draw() {
    drawBoardGrid();
    snake->draw();
    drawFood();
    drawEntities();
    ofDrawBitmapString("Score: " + ofToString(score), 10, 20);
}
//--------------------------------------------------------------
void GameState::keyPressed(int key) {

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
            break;
        case 'u':
            if(snake->getBody().size()>2) snake->removeSegment();
            break;
        case 'p':
            setFinished(true);
            setNextState("PauseState");
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
                if(currentFoodX == snake->getBody()[i][0] and currentFoodY == snake->getBody()[i][1]) {
                    isInSnakeBody = true;
                }
            }
        } while(isInSnakeBody);
        foodSpawned = true;
    }
}
//--------------------------------------------------------------
void GameState::drawFood() {
    ofSetColor(ofColor::red);
    if(foodSpawned) {
        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
    }
}
//--------------------------------------------------------------
void GameState::entitiesSpawner() { //method in charge of creating and adding entities
    if(!entitySpawned){
        rockSpawner();
        rockSpawner();
        rockSpawner();

        treeSpawner();
        treeSpawner();
        
        waterSpawner();
        waterSpawner();
        
    }
}
//--------------------------------------------------------------
void GameState::drawEntities() { //method in charge of drawing all the entities
    if(entitySpawned){
        for(unsigned int i=0;i<entities.size();i++){
            entities[i].draw();
        }
    }

    
}









//--------------------------------------------------------------
// void GameState::drawStartScreen() {
//     ofSetColor(ofColor::black);
//     ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());                                 IMPLEMENTADO EN MENUSTATE
//     ofSetColor(ofColor::white);
//     string text = "Press any arrow key to start.";
//     ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
//     return;
// }
//--------------------------------------------------------------
// void GameState::drawLostScreen() {
//     ofSetColor(ofColor::black);
//     ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());                                 IMPLEMENTADO EN LOSESTATE
//     ofSetColor(ofColor::white);
//     string text = "You lost! Press any arrow key to play again";
//     string text2 = "or press ESC to exit.";
//     ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
//     ofDrawBitmapString(text2, ofGetWidth()/2-8*text2.length()/2, ofGetHeight()/2+2);
//     return;
// }
//--------------------------------------------------------------
void GameState::drawBoardGrid() {
    
    ofDrawGrid(25, 64, false, false, false, true);
    
    // ofSetColor(ofColor::white);
    // for(int i = 0; i <= boardSize; i++) {
    //     ofDrawLine(i*cellSize, 0, i*cellSize, ofGetHeight());
    //     ofDrawLine(0, i*cellSize, ofGetWidth(), i*cellSize);
    // }
}
//--------------------------------------------------------------

void GameState::mousePressed(int x, int y, int button) {
    
}

//--------------------------------------------------------------