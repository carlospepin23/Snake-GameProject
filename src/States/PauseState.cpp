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

    font.load("minecraft.ttf", 32);
    ofSetColor(ofColor::red);
    font.drawString("GAME PAUSED...", ofGetWidth() / 2 - 180, ofGetHeight() / 8);

    ofSetColor(ofColor::white);
    string text = "Press the CONTINUE button to resume the game";
    string text2 = "or press ESC to exit.";
    ofDrawBitmapString(text, ofGetWidth() / 2 - 8 * text.length() / 2, ofGetHeight() / 2 - 11);
    ofDrawBitmapString(text2, ofGetWidth() / 2 - 8 * text2.length() / 2, ofGetHeight() / 2 + 2);

    ofSetColor(ofColor::black);
    continueButton = ofRectangle(font.getStringBoundingBox("CONTINUE", ofGetWidth() / 2 - 110, ofGetHeight() / 2 + 250));
    ofDrawRectangle(continueButton);
    ofSetColor(ofColor::red);
    font.drawString("CONTINUE", ofGetWidth() / 2 - 110, ofGetHeight() / 2 + 250);
}

//--------------------------------------------------------------

void PauseState::keyPressed(int key) {

}

//--------------------------------------------------------------

void PauseState::mousePressed(int x, int y, int button) {
    continueButton = ofRectangle(font.getStringBoundingBox("CONTINUE", ofGetWidth() / 2 - 110, ofGetHeight() / 2 + 250));
    if (continueButton.inside(x, y)) {
        setFinished(true);
        setNextState("GameState");
        return;
    }
}
