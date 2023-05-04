#pragma once

#include "State.h"
#include "ofMain.h"

class MenuState : public State {

public:
    MenuState();
    ~MenuState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void tick() {}
    int getScore(){return 0;}
    bool isPowUp_Activated(){}

    ofTrueTypeFont font;
    
    ofImage backgroundImg;
};