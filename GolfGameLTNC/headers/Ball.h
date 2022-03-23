#pragma once
#include <iostream>
#include <iomanip>
#include "Button.h"
//The Ball that will move around on the screen
class Ball
{
public:
	//The dimensions of the Ball
	static const int Ball_WIDTH = 20;
	static const int Ball_HEIGHT = 20;

	//Maximum axis velocity of the Ball
	static const int Ball_VEL = 640;

	//Initializes the variables
	Ball();

	//Takes key presses and adjusts the Ball's velocity
	void handleEvent(SDL_Event& e);

	//Moves the Ball
	void move(float timeStep);

	//Shows the Ball on the screen
	void render();

	bool Inside();

	float getPosX() {
		return mPosX;
	}

	float getPosY() {
		return mPosY;
	}

private:
	float mPosX, mPosY;
	float mVelX, mVelY;
	float friction = 150;
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
	else if (x > mPosX + Ball_WIDTH)
	{
		inside = false;
	}
	//Mouse above the button
	else if (y < mPosY)
	{
		inside = false;
	}
	//Mouse below the button
	else if (y > mPosY + Ball_HEIGHT)
	{
		inside = false;
	}
	return inside;
}

void Ball::handleEvent(SDL_Event& e)
{
	//TAM THOI DE !INSIDE() VI CHUA NGHI RA CACH KEO THA NEU DAT INSIDE() O DAY
	if (!Inside()) {
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: mVelY -= Ball_VEL; break;
			case SDLK_DOWN: mVelY += Ball_VEL; break;
			case SDLK_LEFT: mVelX -= Ball_VEL; break;
			case SDLK_RIGHT: mVelX += Ball_VEL; break;
			}
		}

		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: mVelY += Ball_VEL; break;
			case SDLK_DOWN: mVelY -= Ball_VEL; break;
			case SDLK_LEFT: mVelX += Ball_VEL; break;
			case SDLK_RIGHT: mVelX -= Ball_VEL; break;
			}
		}

		if (e.type == SDL_MOUSEBUTTONUP) {
			mVelX = 4 * (-e.button.x + mPosX);
			mVelY = 4 * (-e.button.y + mPosY);
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
		else if (mPosX > SCREEN_WIDTH - Ball_WIDTH)
		{
			mPosX = SCREEN_WIDTH - Ball_WIDTH;
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
		else if (mPosY > SCREEN_HEIGHT - Ball_HEIGHT)
		{
			mPosY = SCREEN_HEIGHT - Ball_HEIGHT;
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
		//std::cout << "(" << std::setprecision(2) << std::fixed << mVelX << "," << std::setprecision(2) << std::fixed << mVelY <<"),";
	}
	
}

void Ball::render()
{
	//Show the Ball
	gBallTexture.render((int)mPosX, (int)mPosY);
}

