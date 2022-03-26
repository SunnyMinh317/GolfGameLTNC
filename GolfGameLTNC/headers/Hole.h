#pragma once
#include "Ball.h"
class Hole
{
public:
	//The dimensions of the Hole
	const int Hole_WIDTH = 16;
	const int Hole_HEIGHT = 19;

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

private:
	friend class Ball;
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
	gHoleTexture.render((int)holePosX, (int)holePosY);

}