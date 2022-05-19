#include<SDL.h>
#include <SDL_image.h>
#include "headers\Hole.h"

Hole::Hole()
{
	//set temporary position

	mHole = { (int)holePosX,(int)holePosY,HOLE_WIDTH,HOLE_WIDTH };
}

void Hole::setNewHolePos(int x, int y) {
	holePosX = x;
	holePosY = y;
}

float Hole::getHoleX() {
	return holePosX;
}

float Hole::getHoleY() {
	return holePosY;
}

float Hole::getHoleCenterX() {
	return holePosX + HOLE_WIDTH / 2;
}

float Hole::getHoleCenterY() {
	return holePosY + HOLE_HEIGHT / 2;
}

SDL_Rect Hole::get_Rect() {
	return mHole;
}