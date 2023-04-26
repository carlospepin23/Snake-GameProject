#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetWindowTitle("Snake");

    gameState = new GameState();
    menuState = new MenuState();
    loseState = new LoseState();
    pauseState = new PauseState();
    currentState = menuState;

    sound.load("TetrisOrch.wav");
    sound2.load("8bit.wav");
    sound.setLoop(true);
    sound2.setLoop(true);
    sound2.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    currentState->tick();
    if(currentState->hasFinished()) {
        if(currentState->getNextState() == "GameState") {
            gameState->reset();
            currentState = gameState;
            sound2.stop();
            sound.play();
        } else if(currentState->getNextState() == "LoseState") {
            loseState->reset();
            currentState = loseState;
            sound.stop();
        } else if(currentState->getNextState() == "PauseState") {
            pauseState->reset();
            currentState = pauseState;
            sound2.play();
        }

    }
    currentState->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    currentState->draw();
    // ofSetColor(ofColor::white);
    // if(currentState == gameState) {
    //     ofDrawBitmapString("Current State: GameState", 10, 45);
    // }
    // if(currentState == loseState) {
    //     ofDrawBitmapString("Current State: LoseState", 10, 15);    // Draws the current state of the game.
    // }
    // if(currentState == pauseState) {
    //     ofDrawBitmapString("Current State: PauseState", 10, 15);
    // }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    currentState->keyPressed(key);
    if (key == 'p') {
        sound.stop();
    }
}

//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button) {
    currentState->mousePressed(x, y, button);
    // sound.setPosition(currentSongPosition);
}