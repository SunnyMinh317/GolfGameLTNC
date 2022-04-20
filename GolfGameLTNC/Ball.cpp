#include<SDL.h>
#include<SDL_image.h>
#include"headers\Ball.h"

Ball::Ball()
{
	//Initialize the position
	mPosX = 640 / 2;
	mPosY = 480 / 2;
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
	if (x < mPosX || x > mPosX + BALL_WIDTH || y < mPosY || y > mPosY + BALL_HEIGHT)
	{
		inside = false;
	}
	return inside;
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
		else if (mPosX > 640 - BALL_WIDTH)
		{
			mPosX = 640 - BALL_WIDTH;
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
		else if (mPosY > 480 - BALL_HEIGHT)
		{
			mPosY = 480 - BALL_HEIGHT;
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