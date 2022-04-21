#pragma once
#include <iostream>
#include <iomanip>
//#include "Common.h"
#include "Hole.h"
#include "Texture.h"



//The Ball that will move around on the screen
class Ball : public Hole
{
public:
	//The dimensions of the Ball
	static const int BALL_WIDTH = 20;
	static const int BALL_HEIGHT = 20;

	//Maximum axis velocity of the Ball
	static const int BALL_VEL = 640;

	//Initializes the variables
	Ball();

	//Takes key presses and adjusts the Ball's velocity
	void handleEvent(SDL_Event& e);

	//Moves the Ball
	void move(float timeStep);

	//Shows the Ball on the screen
	void render();

	bool Inside();

	void glow();

	void point(bool spoint, float degree);

	void setInitPos(float x, float y) {
		InitX = x;
		InitY = y;
	}

	void setNewPos(float x, float y) {
		mPosX = x;
		mPosY = y;
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
			std::cout << "You won!";
			win = true;
			//level++ reset pos de het loop
		}
		return win;
	}

	friend class Hole;
private:
	bool spoint,pressed=false;
	float degree;
	float InitX, InitY;
	float mPosX, mPosY;
	float mVelX, mVelY;
	float friction = 100;

	SDL_Rect mBall;
	//Glow dimensions
	int BUTTON_WIDTH = 50;
	int BUTTON_HEIGHT = 50;
};

Ball::Ball()
{
	//Initialize the position
	mPosX = SCREEN_WIDTH/2;
	mPosY = SCREEN_HEIGHT/2;
	mBall = { (int)mPosX,(int)mPosY,BALL_WIDTH,BALL_WIDTH };

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

bool Ball::Inside()
{
	bool inside = true;
	int x, y;
	SDL_GetMouseState(&x, &y);

	//Mouse is left of the button
	if (x < mPosX|| x > mPosX + BALL_WIDTH|| y < mPosY|| y > mPosY + BALL_HEIGHT)
	{
		inside = false;
	}
	return inside;
}

void Ball::glow() {
	if (Inside()) {
		gGlowTexture.render(mPosX - (BUTTON_WIDTH / 2 - 10), mPosY - (BUTTON_HEIGHT / 2 - 10), BUTTON_WIDTH, BUTTON_HEIGHT);
	}
}

void Ball::point(bool spoint,float degree){
	if (spoint) {
		gPointTexture.render(mPosX - (15 / 2 - 10), mPosY - (53 / 2 - 10), 15, 53, degree);
	}
}

void Ball::handleEvent(SDL_Event& e)
{
	spoint = false;
	if (mVelX == 0 && mVelY == 0) {
		if (e.type == SDL_MOUSEBUTTONDOWN && mVelX == 0 && mVelY == 0)
		{
			pressed = true;
			int x;
			int y;
			SDL_GetMouseState(&x, &y);
			setInitPos(x, y);
		}
		if (e.type == SDL_MOUSEMOTION) {
			spoint = true;
			degree = SDL_atan2(-e.button.y + InitY, -e.button.x + InitX) * (180 / 3.1415) + 90;
		}
		if (e.type == SDL_MOUSEBUTTONUP && mVelX == 0 && mVelY == 0)
		{
			pressed = false;
			std::cout << getHoleCenterX() << " " << getHoleCenterY() << std::endl;

			mVelX = 4 * (-e.button.x + InitX);
			mVelY = 4 * (-e.button.y + InitY);

			std::cout << "Hole: " << getHoleX() << " " << getHoleY() << std::endl;
			std::cout << "Ball: " << getPosX() << " " << getPosY() << std::endl;
		}
	}
}



void Ball::move(float timeStep)
{
	if (abs(mVelX) > 0.5 && abs(mVelY) > 0.5) {
		float ax = friction * abs(mVelX / SDL_sqrt(mVelX * mVelX + mVelY * mVelY));
		float ay = friction * abs(mVelY / SDL_sqrt(mVelX * mVelX + mVelY * mVelY));
		//Move the Ball left or right
		mPosX += mVelX * timeStep;

		//If the Ball went too far to the left or right
		if (mPosX < 0)
		{
			mPosX = 0;
			mVelX = -mVelX;
		}
		else if (mPosX > SCREEN_WIDTH - BALL_WIDTH)
		{
			mPosX = SCREEN_WIDTH - BALL_WIDTH;
			mVelX = -mVelX;
		}

		//Move the Ball up or down
		mPosY += mVelY * timeStep;

		//If the Ball went too far up or down
		if (mPosY < 0)
		{
			mPosY = 0;
			mVelY = -mVelY;
		}
		else if (mPosY > SCREEN_HEIGHT - BALL_HEIGHT)
		{
			mPosY = SCREEN_HEIGHT - BALL_HEIGHT;
			mVelY = -mVelY;
		}

		if (mVelX > 0) {
			mVelX -= ax * timeStep;
		}
		else if (mVelX < 0) {
			mVelX += ax * timeStep;
		}

		if (mVelY > 0) {
			mVelY -= ay * timeStep;
		}
		else if (mVelY < 0) {
			mVelY += ay * timeStep;
		}
	}
	else {
		mVelX = 0;
		mVelY = 0;
	}
	
}

void Ball::render()
{
	//Glow the ball
	glow();
	point(spoint&&pressed, degree);
	//Show the Ball
	gBallTexture.render((int)mPosX, (int)mPosY, BALL_WIDTH, BALL_HEIGHT);

	//test point
	//gPointTexture.render((int)mPosX+2, (int)mPosY-32, 16, 64);
}