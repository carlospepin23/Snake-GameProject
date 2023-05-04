#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetWindowTitle("Snake");
    ofSetFrameRate(60);

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
            loseState->displayScore(currentState->getScore());
            currentState = loseState;
            sound.stop();
        } else if(currentState->getNextState() == "PauseState") {
            pauseState->reset();
            currentState = pauseState;
            sound2.play();
        }

    }
    currentState->update();

    if (soundPaused) {
        int elapsedTime = ofGetElapsedTimeMillis() - pausedTime;            // checks the elapsed time since the song was paused
        if (elapsedTime >= 11000) {                                         // checks if the elapsed time is greater than 11 seconds
            sound.play();                                                   // and plays the song again.   
            soundPaused = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    currentState->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    currentState->keyPressed(key);
    if (key == 'p') {
        sound.setPaused(true);
    }
    if (key == 'b' && currentState->isPowUp_Activated()) {
        if (!soundPaused) {
            sound.setPaused(true);
            soundPaused = true;                               // pauses the music and stores the song time position.
            pausedTime = ofGetElapsedTimeMillis();
        }
    }
}

//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button) {
    currentState->mousePressed(x, y, button);
}