#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetWindowTitle("Snake");

    gameState = new GameState();
    menuState = new MenuState();
    loseState = new LoseState();
    currentState = menuState;

    sound.load("TetrisOrch.wav");
    sound.setLoop(true);
    sound.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    if(currentState->hasFinished()) {
        if(currentState->getNextState() == "GameState") {
            gameState->reset();
            currentState = gameState;
        } else if(currentState->getNextState() == "LoseState") {
            loseState->reset();
            currentState = loseState;
        // } else if(currentState->getNextState() == "MenuState") {
        //     menuState->reset();
        //     currentState = menuState;
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
}
//--------------------------------------------------------------