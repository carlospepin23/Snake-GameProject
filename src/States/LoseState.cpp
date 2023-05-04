#include "LoseState.h"

//--------------------------------------------------------------
LoseState::LoseState() {

}   
//--------------------------------------------------------------
LoseState::~LoseState() {

}
//--------------------------------------------------------------
void LoseState::reset() {
    setFinished(false);
    setNextState("");
    return;
}
//--------------------------------------------------------------
void LoseState::update() {

}
//--------------------------------------------------------------
void LoseState::draw() {
    font.load("minecraft.ttf", 28);
    backgroundImg2.load("knight.png");
    backgroundImg2.draw(0, 0, ofGetWidth(), ofGetHeight());

    ofSetColor(ofColor::white);
    string text = "Press any arrow key to play again";
    string text2 = "or press ESC to exit.";
    ofDrawBitmapString(text, ofGetWidth()/2-47*text.length()/2, ofGetHeight()/2-370);
    ofDrawBitmapString(text2, ofGetWidth()/2-70*text2.length()/2, ofGetHeight()/2-356);

    ofSetColor(ofColor::red);
    font.drawString("YOU LOST!", ofGetWidth() / 2 - 110, ofGetHeight() / 4+40);

    ofSetColor(ofColor::white);
    font.drawString("Score: "+ofToString(score),ofGetWidth() / 2 - 736, ofGetHeight() / 2-400);
    // font.drawString("or press ESC to exit.", ofGetWidth() / 2 - 165, ofGetHeight() / 3 + 150);
}
//--------------------------------------------------------------
void LoseState::keyPressed(int key) {
    if(key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_UP || key == OF_KEY_DOWN) {
        setFinished(true);
        setNextState("GameState");
        return;
    }
}

//--------------------------------------------------------------

void LoseState::mousePressed(int x, int y, int button) {

}
