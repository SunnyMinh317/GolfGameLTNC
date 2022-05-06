#include "headers\Mouse.h"
#include <SDL.h>

Mouse::Mouse()
{
	mPosX = 640 / 2;
	mPosY = 480 / 2;
}

void Mouse::handleEvent() {
	SDL_GetMouseState(&mPosX, &mPosY);
}

int Mouse::getPosX() {
	return mPosX;
}

int Mouse::getPosY() {
	return mPosY;
}