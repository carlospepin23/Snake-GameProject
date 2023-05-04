#pragma once

#include "ofMain.h"
#include "State.h"
#include "GameState.h"
#include "MenuState.h"
#include "LoseState.h"
#include "PauseState.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

		void mousePressed(int x, int y, int button);

		State* currentState;
		GameState* gameState;
		MenuState* menuState;
		LoseState* loseState;
		PauseState* pauseState;

		ofSoundPlayer sound;
		double pausedTime = 0;
		bool soundPaused = false;

		// float currentSongPosition = sound.getPosition();
		ofSoundPlayer sound2;
};
