#pragma once
#include "Ball.h"
class Hole
{
public:
	//The dimensions of the Hole
	const int HOLE_WIDTH = 30;
	const int HOLE_HEIGHT = 30;

	//Initializes the variables
	Hole();

	//Shows the Hole on the screen
	void render();
	

	float getHoleX() {
		return holePosX;
	}

	float getHoleY() {
		return holePosY;
	}

	float getHoleCenterX() {
		return holePosX + HOLE_WIDTH / 2;
	}

	float getHoleCenterY() {
		return holePosY + HOLE_HEIGHT / 2;
	}

	SDL_Rect get_Rect() {
		return mHole;
	}
private:
	friend class Ball;
	SDL_Rect mHole;
	float holePosX;
	float holePosY;
};

Hole::Hole()
{
	//set temporary position
	holePosX = 50;
	holePosY = 50;
}

void Hole::render()
{
	//Show the Hole
	gHoleTexture.render((int)holePosX, (int)holePosY, HOLE_WIDTH, HOLE_HEIGHT);

}