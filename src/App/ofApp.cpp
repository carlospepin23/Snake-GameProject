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
    sound.setLoop(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(currentState->hasFinished()) {
        if(currentState->getNextState() == "GameState") {
            gameState->reset();
            currentState = gameState;
            sound.play();
        } else if(currentState->getNextState() == "LoseState") {
            loseState->reset();
            currentState = loseState;
            sound.stop();
        } else if(currentState->getNextState() == "PauseState") {
            pauseState->reset();
            currentState = pauseState;
        }

    }
    currentState->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    currentState->draw();
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
    sound.play();
}