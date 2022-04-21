#pragma once
#include <iostream>
#include <iomanip>
#include <SDL_mixer.h>
#include "Hole.h"



//The Ball that will move around on the screen
class Ball : public Hole
{
public:
	//The dimensions of the Ball
	static const int BALL_WIDTH = 20;
	static const int BALL_HEIGHT = 20;
	static const int BUTTON_WIDTH = 50;
	static const int BUTTON_HEIGHT = 50;

	//Maximum axis velocity of the Ball
	static const int BALL_VEL = 640;

	//Initializes the variables
	Ball();

	//Takes key presses and adjusts the Ball's velocity
	void handleEvent(SDL_Event& e);

	//Moves the Ball
	void move(float timeStep);

	bool Inside();

	void setInitPos(float x, float y) {
		InitX = x;
		InitY = y;
	}

	void setNewPos(float x, float y) {
		mPosX = x;
		mPosY = y;
	}

	float getDegree() {
		return degree;
	}

	bool getPoint() {
		return (pressed && spoint);
	}

	float getPosX() {
		return mPosX;
	}

	float getPosY() {
		return mPosY;
	}

	float getBallCenterX() {
		return mPosX + BALL_WIDTH / 2;
	}

	float getBallCenterY() {
		return mPosY + BALL_HEIGHT / 2;
	}

	SDL_Rect get_Rect() {
		return mBall;
	}

	bool win() {
		bool win = false;
		
		if (SDL_sqrt(pow(getBallCenterX() - getHoleCenterX(),2) + pow(getBallCenterY() - getHoleCenterY(), 2))<=abs(HOLE_WIDTH-BALL_WIDTH)/2) {
			mVelX = 0;
			mVelY = 0;
			mPosX = getHoleX() + 5;
			mPosY = getHoleY() + 5;
			win = true;
		}
		return win;
	}

	int getHitCount();

	friend class Hole;
private:
	bool spoint,pressed=false;
	float degree;
	float InitX, InitY;
	float mPosX, mPosY;
	float mVelX, mVelY;
	float friction = 500;
	int hitCount = 0;
	SDL_Rect mBall;
};