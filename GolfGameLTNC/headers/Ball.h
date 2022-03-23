#pragma once
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

private:
	float mPosX, mPosY;
	float mVelX, mVelY;
};

Ball::Ball()
{
	//Initialize the position
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Ball::handleEvent(SDL_Event& e)
{
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
}

void Ball::move(float timeStep)
{
	//Move the Ball left or right
	mPosX += mVelX * timeStep;

	//If the Ball went too far to the left or right
	if (mPosX < 0)
	{
		mPosX = 0;
	}
	else if (mPosX > SCREEN_WIDTH - Ball_WIDTH)
	{
		mPosX = SCREEN_WIDTH - Ball_WIDTH;
	}

	//Move the Ball up or down
	mPosY += mVelY * timeStep;

	//If the Ball went too far up or down
	if (mPosY < 0)
	{
		mPosY = 0;
	}
	else if (mPosY > SCREEN_HEIGHT - Ball_HEIGHT)
	{
		mPosY = SCREEN_HEIGHT - Ball_HEIGHT;
	}
}

void Ball::render()
{
	//Show the Ball
	gBallTexture.render((int)mPosX, (int)mPosY);
}

