#include "PauseState.h"

//--------------------------------------------------------------

PauseState::PauseState() {

}

//--------------------------------------------------------------

PauseState::~PauseState() {

}

//--------------------------------------------------------------

void PauseState::reset() {
    setFinished(false);
    setNextState("");
    return;
}

//--------------------------------------------------------------

void PauseState::update() {

}

//--------------------------------------------------------------

void PauseState::draw() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "Game paused. Press the Continue button to resume";
    string text2 = "or press ESC to exit.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    ofDrawBitmapString(text2, ofGetWidth()/2-8*text2.length()/2, ofGetHeight()/2+2);

    string text3 = "Continue";
    continueButton = ofRectangle(ofGetWidth()/2-8*text3.length()/2, ofGetHeight()-30, 8*text3.length(), 20);
    ofSetColor(ofColor::white);
    ofDrawRectangle(continueButton);
    return;
}

//--------------------------------------------------------------

void PauseState::keyPressed(int key) {

}

//--------------------------------------------------------------

void PauseState::mousePressed(int x, int y, int button) {
    if (continueButton.inside(x, y)) {
        setFinished(true);
        setNextState("GameState");
        return;
    }
}
