#pragma once
class Hole
{
public:
	//The dimensions of the Hole
	const int HOLE_WIDTH = 30;
	const int HOLE_HEIGHT = 30;

	//Initializes the variables
	Hole();

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
