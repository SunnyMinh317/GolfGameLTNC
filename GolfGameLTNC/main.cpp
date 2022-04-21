/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and, strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TOTAL_LEVEL = 1;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


#include "headers/Texture.h"
#include "headers/Timer.h"

Mix_Music* gSFXBGMusic=NULL;
Mix_Chunk* gSFXPressPlay = NULL;
Mix_Chunk* gSFXHole = NULL;
Mix_Chunk* gSFXLevelUp = NULL;

LTexture gTileTexture;
LTexture gBallTexture;
LTexture gHoleTexture;
LTexture gGlowTexture;
LTexture gPointTexture;
LTexture gTitleMenu;
LTexture gPlayMenu;
LTexture gHitCount;
LTexture MenuScreenBG;
LTexture gEndScreenTitle;
LTexture gEndScreenPlayAgain;
LTexture gLevelNumber;

#include "headers/Ball.h"
#include "headers/Hole.h"
#include "headers/Tile.h"


int level = 0;
//std::vector<Tile> tiles = loadTiles(level);

bool quit = true;
Ball ball;
Hole hole;
SDL_Event event;
LTimer stepTimer;
Tile* tileSet[TOTAL_TILES];
int state = 0; //0 = titleScreen, 1 = transition, 2 = game, 3 = endScreen
SDL_Color black = { 0,0,0 };
SDL_Color white = { 0xFF,0xFF,0xFF };

bool init();
bool loadMedia();
void close();
void loadLevel(int level);
void update();
void game();
void graphics();
void titleScreen();
void transitionScreen();
void renderTransition();
void endScreen();
void renderHitCount();

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
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

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


bool loadMedia()
{

	TTF_Font* gTitleFont = TTF_OpenFont("fonts/pixelFont.ttf", 40);
	TTF_Font* gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 20);
	bool success = true;
	gPointTexture.addRenderer(gRenderer);
	gBallTexture.addRenderer(gRenderer);
	gGlowTexture.addRenderer(gRenderer);
	gHoleTexture.addRenderer(gRenderer);
	gTileTexture.addRenderer(gRenderer);
	MenuScreenBG.addRenderer(gRenderer);
	gPlayMenu.addRenderer(gRenderer);
	gTitleMenu.addRenderer(gRenderer);
	gHitCount.addRenderer(gRenderer);
	gEndScreenTitle.addRenderer(gRenderer);
	gEndScreenPlayAgain.addRenderer(gRenderer);
	gLevelNumber.addRenderer(gRenderer);
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
	if (!MenuScreenBG.loadFromFile("pictures/menuScreenBG.jpg"))
	{
		printf("Failed to load menu screen BG!\n");
		success = false;
	}
	if (gTitleFont == NULL) {
		std::cout << "Failed to load lazy font! SDL_ttf Error: %s\n" << TTF_GetError() << std::endl;
	}
	else {
		
		gTitleMenu.loadFromRenderedText("MINI GOLF A++", black, gTitleFont);
		gPlayMenu.loadFromRenderedText("PRESS ANY KEY TO PLAY!", black, gPlayFont);
		gEndScreenTitle.loadFromRenderedText("YOU WON!", black, gTitleFont);
		gEndScreenPlayAgain.loadFromRenderedText("PRESS ANY KEY TO PLAY AGAIN!", black, gPlayFont);
		

	}
	gSFXBGMusic = Mix_LoadMUS("music/8bitBGMWav.wav");
	gSFXHole = Mix_LoadWAV("music/InHole.wav");
	gSFXLevelUp = Mix_LoadWAV("music/levelUp.wav");
	
	return success;
}

void loadLevel(int level)
{
	std::cout << level << "level" << std::endl;
	if (level > 1)
	{
		state = 3;
		level = 0;
		ball.setNewPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
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
	if (ball.win()) {
		Mix_PlayChannel(-1, gSFXHole, 0);
		SDL_Delay(1000);
		
		level++;
		state = 1;
		
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

	gHoleTexture.render((int)hole.getHoleX(), (int)hole.getHoleY(), hole.HOLE_WIDTH, hole.HOLE_HEIGHT);

	if (ball.Inside()) gGlowTexture.render(ball.getPosX() - (ball.BUTTON_WIDTH / 2 - 10), ball.getPosY() - (ball.BUTTON_HEIGHT / 2 - 10), ball.BUTTON_WIDTH, ball.BUTTON_HEIGHT);

	if (ball.getPoint()) gPointTexture.render(ball.getPosX() - (15 / 2 - 10), ball.getPosY() - (53 / 2 - 10), 15, 53, ball.getDegree());

	gBallTexture.render(ball.getPosX(), ball.getPosY(), ball.BALL_WIDTH, ball.BALL_HEIGHT);

	//gHitCount.render(100, 100);
	renderHitCount();

	//Update screen
	SDL_RenderPresent(gRenderer);

	
}

void titleScreen() {
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			quit = true;
		}
		MenuScreenBG.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		gTitleMenu.render(140, 150);
		gPlayMenu.render(145, 320);
		SDL_RenderPresent(gRenderer);
		if (event.type == SDL_KEYDOWN) {
			Mix_PlayChannel(-1, gSFXHole, 0);
			state++;
		}
	}
	return;
}

void renderTransition() {
	Mix_PlayChannel(-1, gSFXLevelUp, 0);
	SDL_Color black = { 0,0,0 };
	TTF_Font* gTitleFont = TTF_OpenFont("fonts/pixelFont.ttf", 40);
	std::string levelNum = std::to_string(level+1);
	std::cout << "LEVEL = " << levelNum << std::endl;
	std::string levelNumRender = "LEVEL " + levelNum;
	gLevelNumber.loadFromRenderedText(levelNumRender, black, gTitleFont);
	gLevelNumber.render(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);
	SDL_RenderPresent(gRenderer);
}

void transitionScreen() {
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			quit = true;
		}
		MenuScreenBG.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		renderTransition();
		SDL_Delay(1000);
		state++;
	}
}

void endScreen() {
	TTF_Font* gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 25);
	std::string stringHitCount = "FINAL SCORE: " + std::to_string(ball.getHitCount());
	gHitCount.loadFromRenderedText(stringHitCount, black, gPlayFont);
	
	MenuScreenBG.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	gEndScreenTitle.render(200, 150);
	gEndScreenPlayAgain.render(100, 320);
	gHitCount.render(190, 250);
	SDL_RenderPresent(gRenderer);
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			quit = true;
		}
		
		
		if (event.type == SDL_KEYDOWN) {
			Mix_PlayChannel(-1, gSFXHole, 0);
			level = 0;
			state = 1;
		}
	}

	return;
}

void renderHitCount() {
	//TTF_Font* gTitleFont = TTF_OpenFont("fonts/pixelFont.ttf", 40);
	TTF_Font* gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 20);
	std::string stringHitCount = "HIT COUNT: " + std::to_string(ball.getHitCount());
	gHitCount.loadFromRenderedText(stringHitCount, black, gPlayFont);
	gHitCount.render(10, 10);
	SDL_RenderPresent(gRenderer);
}


void game()
{
	if (state == 0)
	{
		titleScreen();
	}
	else if (state == 1) {
		transitionScreen();
	}
	else if (state==2)
	{
		update();
		graphics();
	}
	else if (state == 3) {
		endScreen();
	}
}

void close()
{
	gTileTexture.free();
	gBallTexture.free();
	gHoleTexture.free();
	gGlowTexture.free();
	gPointTexture.free();
	gTitleMenu.free();
	gPlayMenu.free();
	gHitCount.free();
	MenuScreenBG.free();
	gEndScreenTitle.free();
	gEndScreenPlayAgain.free();
	gLevelNumber.free();

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
			Mix_PlayMusic(gSFXBGMusic, -1);
			Mix_VolumeMusic(20);
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





