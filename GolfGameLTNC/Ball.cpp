#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "headers\Ball.h"

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

void Ball::setInitPos(float x, float y) {
	InitX = x;
	InitY = y;
}

void Ball::setNewPos(float x, float y) {
	mPosX = x;
	mPosY = y;
}

void Ball::resetcount() {
	hitCount = 0;
}

float Ball::getDegree() {
	return degree;
}

bool Ball::getPoint() {
	return (pressed && spoint);
}

float Ball::getPosX() {
	return mPosX;
}

float Ball::getPosY() {
	return mPosY;
}

float Ball::getBallCenterX() {
	return mPosX + BALL_WIDTH / 2;
}

float Ball::getBallCenterY() {
	return mPosY + BALL_HEIGHT / 2;
}

float Ball::getPercent() {
	return percent;
}

SDL_Rect Ball::get_Rect() {
	return mBall;
}

bool Ball::win() {
	bool win = false;

	if (SDL_sqrt(pow(getBallCenterX() - getHoleCenterX(), 2) + pow(getBallCenterY() - getHoleCenterY(), 2)) <= abs(HOLE_WIDTH - BALL_WIDTH) / 2) {
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
		if (e.type == SDL_MOUSEBUTTONDOWN )
		{
			pressed = true;
			int x;
			int y;
			SDL_GetMouseState(&x, &y);
			setInitPos(x, y);
		}
		if (e.type == SDL_MOUSEMOTION && pressed==true) {
			spoint = true;
			degree = SDL_atan2(-e.button.y + InitY, -e.button.x + InitX) * (180 / 3.1415) + 90;
			float x = 4 * (-e.button.x + InitX);
			float y = 4 * (-e.button.y + InitY);
			if (SDL_sqrt(x * x + y * y) > MAX_VEL) {
				percent = 1;
			}
			else {
				percent = SDL_sqrt(x * x + y * y) / MAX_VEL;
			}
		}
		if (e.type == SDL_MOUSEBUTTONUP && pressed==true)
		{
			hitCount++;
			Mix_Chunk* gSFXGolfHit = Mix_LoadWAV("music/golfPut.wav");
			Mix_PlayChannel(-1, gSFXGolfHit, 0);
			pressed = false;
			std::cout << getHoleCenterX() << " " << getHoleCenterY() << std::endl;

			mVelX = 4 * (-e.button.x + InitX);
			mVelY = 4 * (-e.button.y + InitY);
			std::cout << "Hole: " << getHoleX() << " " << getHoleY() << std::endl;
			std::cout << "Ball: " << getPosX() << " " << getPosY() << std::endl;
		}
	}
}

SDL_Rect Ball::closest(SDL_Rect ball, SDL_Rect tiles[], int n) {
	SDL_Rect ans = tiles[0];
	float min = SDL_sqrt(((ans.x + ans.w / 2) - (ball.x + ball.w / 2)) * ((ans.x + ans.w / 2) - (ball.x + ball.w / 2)) + ((ans.y + ans.h / 2) - (ball.y + ball.h / 2)) * ((ans.y + ans.h / 2) - (ball.y + ball.h / 2)));
	for (int i = 1; i < n; i++) {
		float x1 = tiles[i].x + tiles[i].w / 2;
		float x2 = ball.x + ball.w / 2;
		float y1 = tiles[i].y + tiles[i].h / 2;
		float y2 = ball.y + ball.h / 2;
		if (SDL_sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) < min) {
			min = SDL_sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
			ans = tiles[i];
		}
	}
	return ans;
}

void Ball::move(float timeStep, SDL_Rect wall[], int n)
{
	mBall = { (int)mPosX,(int)mPosY,BALL_WIDTH,BALL_WIDTH };
	if (abs(mVelX) > 0.5 && abs(mVelY) > 0.5) {
		if (SDL_sqrt(mVelX * mVelX + mVelY * mVelY) > MAX_VEL) {
			mVelX=mVelX/abs(mVelX) * MAX_VEL * abs(mVelX / SDL_sqrt(mVelX * mVelX + mVelY * mVelY));
			mVelY=mVelY/abs(mVelY) * MAX_VEL * abs(mVelY / SDL_sqrt(mVelX * mVelX + mVelY * mVelY));
		}
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

		if (n != 0)
		{
			SDL_Rect clos = closest(mBall, wall, n);

			mBall.x = mPosX + mVelX * timeStep;
			mBall.y = mPosY;

			if (SDL_HasIntersection(&clos, &mBall))
			{
				mVelX = -mVelX;
			}

			mBall.x = mPosX;
			mBall.y = mPosY + mVelY * timeStep;

			if (SDL_HasIntersection(&clos, &mBall))
			{
				mVelY = -mVelY;
			}
		}
	}
	else {
		mVelX = 0;
		mVelY = 0;
	}

}

int Ball::getHitCount() {
	return hitCount;
}