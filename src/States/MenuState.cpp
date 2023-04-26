#include "MenuState.h"

//--------------------------------------------------------------
MenuState::MenuState() {

}   
//--------------------------------------------------------------
MenuState::~MenuState() {

}
//--------------------------------------------------------------
void MenuState::reset() {
    setFinished(false);
    setNextState("");
    return;
}
//--------------------------------------------------------------
void MenuState::update() {

}
//--------------------------------------------------------------
void MenuState::draw() {
    // ofSetColor(ofColor::black);
    // ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    font.load("minecraft.ttf", 28);
    backgroundImg.load("nature.png");
    backgroundImg.draw(0, 0, ofGetWidth(), ofGetHeight());

    ofSetColor(ofColor::blue);
    font.drawString("WELCOME TO SNAKE!", ofGetWidth() / 2 - 212, ofGetHeight() / 3 + 20);
    // font.drawString("Press any arrow key to start.", ofGetWidth() / 2 - 330, ofGetHeight() / 3 + 150);
    ofSetColor(ofColor::white);
    string text = "Press any arrow key to start.";
    ofDrawBitmapString(text, ofGetWidth() / 2 - 8 * text.length() / 2, ofGetHeight() / 2 - 70);
}
//--------------------------------------------------------------
void MenuState::keyPressed(int key) {
    if(key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_UP || key == OF_KEY_DOWN) {
        setFinished(true);
        setNextState("GameState");
        return;
    }
}

//--------------------------------------------------------------

void MenuState::mousePressed(int x, int y, int button) {

}