#pragma once

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

private:
	float PosX, PosY;
};

Hole::Hole()
{
	//set temporary position
	PosX = 50;
	PosY = 50;
}

void Hole::render()
{
	//Show the Hole
	gHoleTexture.render((int)PosX, (int)PosY);
}