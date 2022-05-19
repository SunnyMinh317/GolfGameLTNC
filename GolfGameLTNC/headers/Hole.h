#pragma once
class Hole
{
public:
	//The dimensions of the Hole
	const int HOLE_WIDTH = 30;
	const int HOLE_HEIGHT = 30;

	//Initializes the variables
	//Initializes the variables
	Hole();
	void setNewHolePos(int, int);
	float getHoleX();
	float getHoleY();
	float getHoleCenterX();
	float getHoleCenterY();

	SDL_Rect get_Rect();
private:
	friend class Ball;
	SDL_Rect mHole;
	float holePosX = 50;
	float holePosY = 50;
};
