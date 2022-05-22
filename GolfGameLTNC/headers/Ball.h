#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
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
	static const int MAX_VEL = 800;

	//Maximum axis velocity of the Ball
	static const int BALL_VEL = 640;

	//Initializes the variables
	Ball();

	//Takes key presses and adjusts the Ball's velocity
	void handleEvent(SDL_Event& e);

	//Moves the Ball
	void move(float timeStep, std::vector<SDL_Rect>, std::vector<SDL_Rect>, std::vector<SDL_Rect>);
	bool Inside();

	void setInitPos(float x, float y);

	void setNewPos(float x, float y);

	void resetcount();

	float getDegree();

	bool getPoint();

	bool inSand();

	float getPosX();

	float getPosY();

	float getBallCenterX();

	float getBallCenterY();

	float getPercent();

	SDL_Rect get_Rect();

	SDL_Rect closest(SDL_Rect ball, std::vector<SDL_Rect> tiles);

	bool win();

	int getHitCount();

	friend class Hole;
private:
	bool spoint,pressed=false;
	float degree, percent;
	float InitX, InitY, InitBallX, InitBallY;
	float mPosX, mPosY;
	float mVelX, mVelY;
	float friction = 500;
	bool checkSand = false;
	int hitCount = 0;
	SDL_Rect mBall;
};