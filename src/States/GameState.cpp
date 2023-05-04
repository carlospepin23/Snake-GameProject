#include "GameState.h"

//--------------------------------------------------------------
GameState::GameState() {
    foodSpawned = false;
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    sound3.load("pacman.wav");
    sound4.load("GodMode.wav");
    sound5.load("fast.wav");
    sound6.load("BetterApple.wav");
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
    if(On_Off) On_Off=!On_Off;
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
        powUp_PacMan_Mode=false;
        sound3.stop();
        sound4.stop();
        sound5.stop();
        sound6.stop();
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
            if(snake->isInmortal()==false && powUp_PacMan_Mode==false) { 
                snake->setCrashed(true);
            } 
            else if(snake->isInmortal()==true && powUp_PacMan_Mode==false) {
                snake->ignoreCrash();
            }
            else {
                if (powUp_PacMan_Mode == true) {
                    entities.erase(entities.begin()+i);
                }
            }
        }  
    }

    int updateCount = powUp_Speed_Boost ? 5 : 10;
    if(ofGetFrameNum() % updateCount == 0) {
            snake->update();
    }

    if (snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY) {
        score += 10;
        p_score=(p_score%260)+10;
    }
}
//--------------------------------------------------------------
void GameState::draw() {
    drawBoardGrid();
    if(On_Off){ //Dibuja el GPS
        path.clear();
        crossedPath.clear();
        crossedPath.resize(boardSizeWidth, vector<int>(boardSizeHeight, 0));
        GPS(snake->getHead()[0],snake->getHead()[1],path);
        drawPath();
    }
    snake->draw();
    drawFood();
    drawEntities();
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Score: " + ofToString(score), 10, 15);
    ofDrawBitmapString("Current Power Up: " + pow_up_s, 10, 30);
    if(powUp_Speed_Boost==true){
        ofDrawBitmapString("SpeedBoost remaining seconds: " + ofToString(timer-seconds), 10, 45);
    }
    else if(snake->isInmortal()){
        ofDrawBitmapString("GodMode remaining seconds: " + ofToString(timer-seconds), 10, 45);
    }
    else if(powUp_PacMan_Mode==true){
        ofDrawBitmapString("PacMan Mode remaining seconds: " + ofToString(timer-seconds), 10, 45);
    }
    else {
        if (foodSpawned==true && pow_up != 1 && pow_up != 2 && pow_up != 3 && pow_up != 4){
            ofDrawBitmapString("Hurry! Get the food: " + ofToString(30-decayCounter), 10, 45);
        }
        else{
            ofDrawBitmapString("A PowerUp has spawned!", 10, 45);
        }
    }
    
    if(decayCounter > previousDecayCounter && pow_up != 1 && pow_up != 2 && pow_up != 3 && pow_up != 4){
        previousDecayCounter = decayCounter;
        red -= 4;
        green += 3;
    }

    if(decayCounter == 30 && pow_up != 1 && pow_up != 2 && pow_up != 3 && pow_up != 4){
        foodSpawned = false;
    }
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
            p_score=(p_score%260)+10;
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
                sound5.play();
                ticks=0;
                seconds=0;
                timer=15;
                powUp_Speed_Boost=true;
            }
            else if(pow_up_s=="BetterApple"){
                sound6.play();
                powUp_Better_Apple=true;
            }
            else if(pow_up_s=="GodMode"){
                sound4.play();
                ticks=0;
                seconds=0;
                timer=10;
                snake->setInmortal(true);
            }
            else if(pow_up_s=="PacMan"){
                sound3.play();
                ticks=0;
                seconds=0;
                timer=10;
                powUp_PacMan_Mode=true;
            }
            pow_up_s="None";
            break;
        case 'g':
            On_Off=!On_Off;
    }
}
//--------------------------------------------------------------
void GameState::foodSpawner() {
    if(!foodSpawned) {                                                             
        bool isInSnakeBody;
        bool isInEntities;
        do {
            isInSnakeBody = false;
            isInEntities = false;
            currentFoodX = ofRandom(1, boardSizeWidth-1);
            currentFoodY = ofRandom(1, boardSizeHeight-1);
            for(unsigned int i = 0; i < snake->getBody().size(); i++) {
                if(currentFoodX == snake->getBody()[i][0] and currentFoodY == snake->getBody()[i][1]){
                    isInSnakeBody = true;
                }
            }
            if (!isInSnakeBody) {
                for (unsigned int i = 0; i < entities.size(); i++) {
                    if(currentFoodX == entities[i].getEntityX() && currentFoodY == entities[i].getEntityY()){
                        isInEntities = true;
                    }
                }
            }
        } while(isInSnakeBody || isInEntities);
        powUpDisplay(p_score);
        if(On_Off) On_Off=!On_Off;
        foodSpawned = true;
        red = 255;
        green = 0;
        decayCounter = 0;
        previousDecayCounter = 0;
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
            case 4:
                ofSetColor(ofColor::yellow);
                ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
                break;
            default:
                ofSetColor(red, green, 0);
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
    else if(p_score==250) pow_up=4;
    else pow_up=0;
    
}

//--------------------------------------------------------------

void GameState::powUpDisplay(int p_score){

    //Texto PowUps
    if(p_score==60) pow_up_s="SpeedBoost";
    else if (p_score==110 && powUp_Better_Apple==false) pow_up_s="BetterApple";
    else if (p_score==160) pow_up_s="GodMode";
    else if (p_score==260) pow_up_s="PacMan";
}

//--------------------------------------------------------------

void GameState::tick(){
    ticks++;
    if(ticks % 60 == 0){ //60 ticks son un segundo
        seconds+=1;
        decayCounter+=1;
    }
    if(powUp_Speed_Boost==true){
        if(seconds>=timer) powUp_Speed_Boost=false;
    }
    else if(snake->isInmortal()){
        if(seconds>=timer){
            snake->setInmortal(false); 
        }
    }
    else if(powUp_PacMan_Mode==true){
        if(seconds>=timer) powUp_PacMan_Mode=false;
    }
}
//--------------------------------------------------------------


bool GameState::GPS(int row, int col, vector<pair<int, int>>& path) {
    int snakeX=snake->getHead()[0];
    int snakeY=snake->getHead()[1]; 
    // Chequea que el snake este dentro de los limites
    if (row < 0 || row >= boardSizeWidth || col < 0 || col >= boardSizeHeight) {
        return false;
    }

    if (crossedPath[row][col] != 0) return false;

    //Search Sharpener
    
    //SNAKE IZQUIERDA DE MANZANA
    if(snakeX<=currentFoodX){
        if(row>currentFoodX || row<snake->getHead()[0]) return false;
    }
    //SNAKE DERECHA DE MANZANA
    if(snakeX>=currentFoodX){
        if(row<currentFoodX || row>snake->getHead()[0]) return false;
    }
    //SNAKE ARRIBA DE MANZANA
    if(snakeY<=currentFoodY){
        if(col>currentFoodY || col<snake->getHead()[1]) return false;
    }
    //SNAKE ABAJO DE MANZANA
    if(snakeY>=currentFoodY){
        if(col<currentFoodY || col>snake->getHead()[1]) return false;
    }

    // Chequea si el snake encontro la manzana
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

    // Marca la posicion corrinte como visitada
    crossedPath[row][col] = -1;

    //Bulk Decision MAKING (Binary Search IDEA)

    //Snake IZQUIERDA Y ARRIBA  //CUBRE POLO OESTE
    if(snakeX<=currentFoodX && snakeY<currentFoodY){
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
    }         
    //Snake IZQUERDA Y ABAJO //CUBRE POLO NORTE
    if(snakeX<currentFoodX && snakeY>=currentFoodY){
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

        // Search Right
        if (GPS(row, col+1, path)) {
            path.emplace_back(row, col);
            return true;
        }

    }           
    //Snake DERECHA Y ARRIBA //CUBRE POLO SUR
    if(snakeX>currentFoodX && snakeY<=currentFoodY){

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

        // Search Left
        if (GPS(row, col-1, path)) {
            path.emplace_back(row, col);
            return true;
        }

    }   //Snake DERECHA Y ABAJO //CUBRE POLO ESTE
    if(snakeX>=currentFoodX && snakeY>currentFoodY){
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

    // Marca la posicion corriente como no visitada
    crossedPath[row][col] = 0;

    // No se encuentra el camino
    return false;
}
