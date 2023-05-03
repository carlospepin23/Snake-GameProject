#include "GameState.h"

//--------------------------------------------------------------
GameState::GameState() {
    foodSpawned = false;
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    crossedPath.resize(boardSizeWidth, vector<int>(boardSizeHeight, 0));
}
//--------------------------------------------------------------
GameState::~GameState() {
    delete snake;
    entities.clear();
}
//--------------------------------------------------------------
void GameState::reset() {
    if(getNextState() == "PauseState") {
        setFinished(false);
        setNextState("");
        return;
    }
    else {
    delete snake;
    entities.clear();
    path.clear();
    crossedPath.clear();
    crossedPath.resize(boardSizeWidth, vector<int>(boardSizeHeight, 0));
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
        pow_up_s="None";
        last_score=score;
        score = 0;
        p_score = 0;
        ticks=0;
        seconds=0;
        powUp_Better_Apple=false;
        powUp_Speed_Boost=false;
        return;

    }

    if(snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY){
        if(powUp_Better_Apple==true){
            snake->grow();
            snake->grow();
        }
        else{
            snake->grow();
        }
        foodSpawned = false;
    }
    
    powUpManager(this->p_score);
    foodSpawner();
    entitiesSpawner();

    for(unsigned int i=0;i<entities.size();i++){
        if(snake->getHead()[0] == entities[i].getEntityX() && snake->getHead()[1] == entities[i].getEntityY()){
            if(snake->isInmortal()==false) snake->setCrashed(true);
            else snake->stop();
        }  
    }

    int updateCount = powUp_Speed_Boost ? 5 : 10;
    if(ofGetFrameNum() % updateCount == 0) {
            snake->update();
    }

    if (snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY) {
        score += 10;
        p_score=(p_score%150)+10;
    }
}
//--------------------------------------------------------------
void GameState::draw() {
    drawBoardGrid();
    snake->draw();
    drawFood();
    drawEntities();
    drawPath();
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Score: " + ofToString(score), 10, 15);
    ofDrawBitmapString("Current Power Up: " + pow_up_s, 10, 30);
    if(powUp_Speed_Boost==true){
        ofDrawBitmapString("SpeedBoost remaining seconds: " + ofToString(timer-seconds), 10, 45);
    }
    else if(snake->isInmortal()){
        ofDrawBitmapString("GodMode remaining seconds: " + ofToString(timer-seconds), 10, 45);
    }
}
//--------------------------------------------------------------
void GameState::keyPressed(int key) {

    // if(key != OF_KEY_LEFT && key != OF_KEY_RIGHT && key != OF_KEY_UP && key != OF_KEY_DOWN && key !='a' && key!='u' && key!='b' && key!='p') { return; }

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
        case 'p':
            setFinished(true);
            setNextState("PauseState");
            break;
        case 'b':
            //Declarar el codigo de los powerups
            if(pow_up_s=="SpeedBoost"){
                ticks=0;
                seconds=0;
                timer=15;
                powUp_Speed_Boost=true;
            }
            else if(pow_up_s=="BetterApple"){
                powUp_Better_Apple=true;
            }
            else if(pow_up_s=="GodMode"){
                ticks=0;
                seconds=0;
                timer=10;
                snake->setInmortal(true);
            }
            pow_up_s="None";
            break;
        case 'g':
            On_Off=!On_Off;
            path.clear();
            crossedPath.clear();
            crossedPath.resize(boardSizeWidth, vector<int>(boardSizeHeight, 0));
            if(On_Off==true){
                GPS(snake->getHead()[0],snake->getHead()[1],path);
            }
    }
}
//--------------------------------------------------------------
void GameState::foodSpawner() {
    if(!foodSpawned) {                                                                                  //Make compatible with speedBoost powup
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
        path.clear();
        crossedPath.clear();
        crossedPath.resize(boardSizeWidth, vector<int>(boardSizeHeight, 0));
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
        for(int i = 0; i < 20; i++){
            int randNum = ofRandom(1,4);
            if(randNum == 1) rockSpawner();
            else if(randNum == 2) treeSpawner();
            else if(randNum == 3) waterSpawner();

        }
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

void GameState::drawBoardGrid() {
    ofSetBackgroundColor(ofColor::black);
    ofDrawGrid(25, 64, false, false, false, true);
}
//--------------------------------------------------------------

void GameState::powUpManager(int p_score){

    //Spawner
    if(p_score==50) pow_up=1;
    else if(p_score==100 && powUp_Better_Apple==false) pow_up=2;
    else if(p_score==150) pow_up=3;
    else pow_up=0;
    
}

//--------------------------------------------------------------

void GameState::powUpDisplay(int p_score){

    //Texto PowUps
    if(p_score==60) pow_up_s="SpeedBoost";
    else if (p_score==110 && powUp_Better_Apple==false) pow_up_s="BetterApple";
    else if (p_score==10 && score!=10) pow_up_s="GodMode";
}

//--------------------------------------------------------------

void GameState::tick(){
    ticks++;
    if(ticks % 60 == 0){ //60 because 60 ticks are 1 second
        seconds+=1;
    }
    if(powUp_Speed_Boost==true){
        if(seconds>=timer) powUp_Speed_Boost=false;
    }
    else if(snake->isInmortal()) if(seconds>=timer) snake->setInmortal(false);          
    
}
//--------------------------------------------------------------


bool GameState::GPS(int row, int col, vector<pair<int, int>>& path) {
    int snakeX=snake->getHead()[0];
    int snakeY=snake->getHead()[1]; 
    // Check if the snake is within the bounds of the maze
    if (row < 0 || row >= boardSizeWidth || col < 0 || col >= boardSizeHeight) {
        return false;
    }

    if (crossedPath[row][col] != 0) return false;

    //Search Sharpener
    
    //SNAKE IZQUIERDA DE MANZANA
    if(snakeX<currentFoodX){
        if(row>currentFoodX || row<snake->getHead()[0]) return false;
    }
    //SNAKE DERECHA DE MANZANA
    if(snakeX>currentFoodX){
        if(row<currentFoodX || row>snake->getHead()[0]) return false;
    }
    //SNAKE ARRIBA DE MANZANA
    if(snakeY<currentFoodY){
        if(col>currentFoodY || col<snake->getHead()[1]) return false;
    }
    //SNAKE ABAJO DE MANZANA
    if(snakeY>currentFoodY){
        if(col<currentFoodY || col>snake->getHead()[1]) return false;
    }

    // Check if the snake found the apple
    if (currentFoodX == row && currentFoodY == col) {
        path.emplace_back(row, col);
        return true;
    }
    //Chequea si snake encuentra entities
    if(hasCrashed_Entities(row,col,0)){
        return false;
    }

    // Check if the snake revisited a space
    if (!crossedPath.empty() && crossedPath[row][col] == -1) {
        path.emplace_back(row, col);
        return false;
    }

    // Mark the current cell as visited
    crossedPath[row][col] = -1;

    //Bulk Decision MAKING (Binary Search IDEA)

            //IZQUIERDA                             //ARRIBA
    if(snakeX<currentFoodX && snakeY<currentFoodY){
        // Search Right
        if (GPS(row, col+1, path)) {
            path.emplace_back(row, col);
            return true;
        }

        // Search Down
        if (GPS(row+1, col, path)) {
            path.emplace_back(row, col);
            return true;
        }

        // Search Left
        if (GPS(row, col-1, path)) {
            path.emplace_back(row, col);
            return true;
        }

        // Search Up
        if (GPS(row-1, col, path)) {
            path.emplace_back(row, col);
            return true;
        }
    }          //IZQUERDA                           //ABAJO
    if(snakeX<currentFoodX && snakeY>currentFoodY){
        // Search Right
        if (GPS(row, col+1, path)) {
            path.emplace_back(row, col);
            return true;
        }

        // Search Up
        if (GPS(row-1, col, path)) {
            path.emplace_back(row, col);
            return true;
        }

        // Search Left
        if (GPS(row, col-1, path)) {
            path.emplace_back(row, col);
            return true;
        }

        // Search Down
        if (GPS(row+1, col, path)) {
            path.emplace_back(row, col);
            return true;
        }
    }           //DERECHA                               //ARRIBA
    if(snakeX>currentFoodX && snakeY<currentFoodY){
        // Search Left
        if (GPS(row, col-1, path)) {
            path.emplace_back(row, col);
            return true;
        }

        // Search Down
        if (GPS(row+1, col, path)) {
            path.emplace_back(row, col);
            return true;
        }

        // Search Right
        if (GPS(row, col+1, path)) {
            path.emplace_back(row, col);
            return true;
        }

        // Search Up
        if (GPS(row-1, col, path)) {
            path.emplace_back(row, col);
            return true;
        }

    }              //DERECHA                        ABAJO
    if(snakeX>currentFoodX && snakeY>currentFoodY){
        // Search Left
        if (GPS(row, col-1, path)) {
            path.emplace_back(row, col);
            return true;
        }

        // Search Up
        if (GPS(row-1, col, path)) {
            path.emplace_back(row, col);
            return true;
        }

        // Search Right
        if (GPS(row, col+1, path)) {
            path.emplace_back(row, col);
            return true;
        }

        // Search Down
        if (GPS(row+1, col, path)) {
            path.emplace_back(row, col);
            return true;
        }

    }


    // Mark the current cell as unvisited
    crossedPath[row][col] = 0;

    // No path found
    return false;
}
