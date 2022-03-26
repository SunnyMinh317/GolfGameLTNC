#pragma once
#include<iostream>
#include "Texture.h"
#include "Ball.h"
const int BUTTON_WIDTH = 50;
const int BUTTON_HEIGHT = 50;
const int TOTAL_BUTTONS = 4;


//The mouse button
class LButton
{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(float x, float y);

	//Handles mouse event
	void handleEvent(SDL_Event& e);

	//Shows button sprite
	void render();

	bool Inside();
	friend class Ball;

private:
	//Top left position
	SDL_Point mPosition;

	//Currently used global sprite
	Uint8 mCurrentAlpha;
};

SDL_Rect gSpriteClips = { 0,0,BUTTON_WIDTH,BUTTON_HEIGHT };

LButton GButton;

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentAlpha = 0;
}

void LButton::setPosition(float x, float y)
{
	mPosition.x = x;
	mPosition.y = y;
}

bool LButton::Inside()
{
	bool inside = true;
	int x, y;
	SDL_GetMouseState(&x, &y);

	//Mouse is left of the button
	if (x < mPosition.x)
	{
		inside = false;
	}
	//Mouse is right of the button
	else if (x > mPosition.x + BUTTON_WIDTH)
	{
		inside = false;
	}
	//Mouse above the button
	else if (y < mPosition.y)
	{
		inside = false;
	}
	//Mouse below the button
	else if (y > mPosition.y + BUTTON_HEIGHT)
	{
		inside = false;
	}
	return inside;
}

void LButton::handleEvent(SDL_Event& e)
{
	//If mouse event happened
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{

		//Mouse is outside button
		if (!Inside())
		{
			mCurrentAlpha = 0;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				mCurrentAlpha = 255;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentAlpha = 255;
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentAlpha = 255;
				break;
			}
		}
	}
}

void LButton::render()
{
	gGlowTexture.setAlpha(mCurrentAlpha);
	//Show current button sprite
	//gGlowTexture.render(mPosition.x - (BUTTON_WIDTH/2 - 10), mPosition.y - (BUTTON_HEIGHT/ 2 - 10), BUTTON_WIDTH, BUTTON_HEIGHT);
}
