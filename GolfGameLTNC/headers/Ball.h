#pragma once
#include <iostream>
#include <iomanip>
#include "Button.h"
#include "Hole.h"


LTexture gGlowTexture;

LTexture gPointTexture;

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

	void point();

	void setInitPos(float x, float y) {
		InitX = x;
		InitY = y;
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
		return mPosY - BALL_HEIGHT / 2;
	}

	bool win() {
		bool win = false;
		
		if (SDL_sqrt(pow(getBallCenterX() - getHoleCenterX(),2) + pow(getBallCenterY() - getHoleCenterY(), 2))<=abs(HOLE_WIDTH-BALL_WIDTH)) {
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
	float InitX, InitY;
	float mPosX, mPosY;
	float mVelX, mVelY;
	float friction = 100;

	//Glow dimensions
	int BUTTON_WIDTH = 50;
	int BUTTON_HEIGHT = 50;
};

Ball::Ball()
{
	//Initialize the position
	mPosX = SCREEN_WIDTH/2;
	mPosY = SCREEN_HEIGHT/2;

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
	if (x < mPosX)
	{
		inside = false;
	}
	//Mouse is right of the button
	else if (x > mPosX + BALL_WIDTH)
	{
		inside = false;
	}
	//Mouse above the button
	else if (y < mPosY)
	{
		inside = false;
	}
	//Mouse below the button
	else if (y > mPosY + BALL_HEIGHT)
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

void Ball::point() {
	gPointTexture.render(mPosX - (100 / 2 - 10), mPosY - (200 / 2 - 10), 100, 200, NULL, 0.0);
}

void Ball::handleEvent(SDL_Event& e)
{
	if (mVelX == 0 && mVelY == 0) {
		if (e.type == SDL_MOUSEBUTTONDOWN && mVelX == 0 && mVelY == 0)
		{
			int x;
			int y;
			SDL_GetMouseState(&x, &y);
			setInitPos(x, y);
		}
		if (e.type == SDL_MOUSEMOTION) {
			this->point();
		}
		else if (e.type == SDL_MOUSEBUTTONUP && mVelX == 0 && mVelY == 0)
		{
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
	if (abs(mVelX) > 0.1 && abs(mVelY) > 0.1) {
		float ax = friction * abs(mVelX) / abs(mVelY);
		float ay = friction * abs(mVelY) / abs(mVelX);
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

	//Show the Ball
	gBallTexture.render((int)mPosX, (int)mPosY, BALL_WIDTH, BALL_HEIGHT);
}

