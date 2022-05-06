#pragma once
#include <iostream>
#include <iomanip>

class Mouse
{
public:
	//The dimensions of the Ball
	static const int MOUSE_WIDTH = 15;
	static const int MOUSE_HEIGHT = 19;

	Mouse();

	void handleEvent();

	int getPosX();

	int getPosY();

private:
	int mPosX, mPosY;
};