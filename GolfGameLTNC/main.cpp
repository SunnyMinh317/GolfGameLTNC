/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and, strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

#include "headers/Texture.h"
#include "headers/Timer.h"

LTexture gTileTexture;
LTexture gBallTexture;
LTexture gHoleTexture;
LTexture gGlowTexture;
LTexture gPointTexture;

#include "headers/Ball.h"
#include "headers/Hole.h"
#include "headers/Tile.h"



bool init();
bool loadMedia();
void close();
void loadLevel(int level);
void update();
void game();
void graphics();
void titleScreen();

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;
	if (!gPointTexture.loadFromFile("pictures/point.png"))
	{
		printf("Failed to load Point texture!\n");
		success = false;
	}
	if (!gBallTexture.loadFromFile("pictures/tileset/Golfball.png"))
	{
		printf("Failed to load Ball texture!\n");
		success = false;
	}
	if (!gGlowTexture.loadFromFile("pictures/GolfGlow.png")) {
		printf("Failed to load Glow texture!\n");
		success = false;
	}
	if (!gHoleTexture.loadFromFile("pictures/hole2.png"))
	{
		printf("Failed to load Hole texture!\n");
		success = false;
	}
	if (!gTileTexture.loadFromFile("pictures/tileset/tilemap.png"))
	{
		printf("Failed to load Hole texture!\n");
		success = false;
	}
	return success;
}

int level = 0;
//std::vector<Tile> tiles = loadTiles(level);

bool quit = true;
Ball ball;
Hole hole;
SDL_Event event;
LTimer stepTimer;
Tile* tileSet[TOTAL_TILES];
int state = 1; //0 = title screen, 1 = game, 2 = end screen



void loadLevel(int level)
{
	std::cout << level << "level" << std::endl;
	if (level > 1)
	{
		state = 2;
		return;
	}
	switch (level)
	{
	case 0:
		ball.setNewPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		setTiles(tileSet, "headers/tile.map");
		break;
	case 1:
		ball.setNewPos(SCREEN_WIDTH / 2+200, SCREEN_HEIGHT / 2+200);
		setTiles(tileSet, "headers/tile2.map");
		break;
	}	

}

void update()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type==SDL_QUIT){
			quit = true;
		}
		
		ball.handleEvent(event);
		
	}
	float timeStep = stepTimer.getTicks() / 1000.f;
	ball.move(timeStep);
	stepTimer.start();
	if (ball.win() && state==1) {
		level++;
		loadLevel(level);
	}
}

void graphics()
{
	SDL_SetRenderDrawColor(gRenderer, 0x80, 0xC6, 0x72, 0xFF);
	SDL_RenderClear(gRenderer);

	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		tileSet[i]->render();
	}
	//Render Hole
	hole.render();

	//Render Ball
	ball.render();

	//Update screen
	SDL_RenderPresent(gRenderer);

	
}

void titleScreen() {
	return;
}



void game()
{
	if (state == 0)
	{
		titleScreen();
	}
	else
	{
		update();
		graphics();
	}
}

void close()
{

	gGlowTexture.free();
	gBallTexture.free();
	gHoleTexture.free();
	gPointTexture.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			quit = false;
			loadLevel(level);
			//While application is running
			while (!quit)
			{
				game();
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}





