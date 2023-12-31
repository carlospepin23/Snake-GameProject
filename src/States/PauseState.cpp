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

void PauseState::draw() {
    font.load("minecraft.ttf", 32);
    backgroundImg.load("coffee.png");
    backgroundImg.draw(0, 0, ofGetWidth(), ofGetHeight());

    ofSetColor(ofColor::blue);
    font.drawString("GAME PAUSED...", ofGetWidth() / 2 - 510, ofGetHeight() / 3 + 15);

    ofSetColor(ofColor::white);
    ofRectangle continueButton = font.getStringBoundingBox("CONTINUE", ofGetWidth() / 2 - 128, ofGetHeight() / 2 + 380);
    font.drawString("CONTINUE", ofGetWidth() / 2 - continueButton.width / 2, ofGetHeight() / 2 + 380 + continueButton.height);

}

//--------------------------------------------------------------

void PauseState::keyPressed(int key) {

}

//--------------------------------------------------------------

void PauseState::mousePressed(int x, int y, int button) {
    ofRectangle continueButton = font.getStringBoundingBox("CONTINUE", ofGetWidth() / 2 - 128, ofGetHeight() / 2 + 380);
    if (x >= ofGetWidth() / 2 - continueButton.width / 2 && x <= ofGetWidth() / 2 + continueButton.width / 2 &&
        y >= ofGetHeight() / 2 + 380 && y <= ofGetHeight() / 2 + 380 + continueButton.height) {
        setFinished(true);
        setNextState("GameState");
        return;
    }
}
