#pragma once

class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 640;

	//Initializes the variables
	Dot();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move(float timeStep);

	//Shows the dot on the screen
	void render();

private:
	float mPosX, mPosY;
	float mVelX, mVelY;
};

Dot::Dot()
{
	//Initialize the position
	mPosX = SCREEN_WIDTH / 2;
	mPosY = SCREEN_HEIGHT / 2;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Dot::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY -= DOT_VEL; break;
		case SDLK_DOWN: mVelY += DOT_VEL; break;
		case SDLK_LEFT: mVelX -= DOT_VEL; break;
		case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += DOT_VEL; break;
		case SDLK_DOWN: mVelY -= DOT_VEL; break;
		case SDLK_LEFT: mVelX += DOT_VEL; break;
		case SDLK_RIGHT: mVelX -= DOT_VEL; break;
		}
	}

	if (e.type == SDL_MOUSEBUTTONUP) {
		mVelX = 4 * (-e.button.x + mPosX);
		mVelY = 4 * (-e.button.y + mPosY);
	}
}

void Dot::move(float timeStep)
{
	if (abs(mVelX) > 0.1 && abs(mVelY) > 0.1) {
		float ax = 100 * (abs(mVelX) / abs(mVelY));
		float ay = 100 * (abs(mVelY) / abs(mVelX));
		//Move the dot left or right


		//If the dot went too far to the left or right
		if (mPosX < 0 || mPosX > SCREEN_WIDTH - DOT_WIDTH)
		{
			if (mPosX < 0) mPosX = 0;
			else if (mPosX > SCREEN_WIDTH - DOT_WIDTH) mPosX = SCREEN_WIDTH - DOT_WIDTH;
			mVelX = -mVelX;


		}


		//Move the dot up or down

		//If the dot went too far up or down
		if (mPosY < 0 || mPosY > SCREEN_HEIGHT - DOT_HEIGHT)
		{
			if (mPosY < 0) mPosY = 0;
			else if (mPosY > SCREEN_HEIGHT - DOT_HEIGHT) mPosY = SCREEN_HEIGHT - DOT_HEIGHT;
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
		mPosY += mVelY * timeStep;
		mPosX += mVelX * timeStep;

		std::cout << "Velocity: " << mVelX << " " << mVelY << std::endl;
		std::cout << "Positon: " << mPosX << " " << mPosY << std::endl;
	}

}

void Dot::render()
{
	//Show the dot
	gDotTexture.render((int)mPosX, (int)mPosY);
}

