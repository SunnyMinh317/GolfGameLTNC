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

LTexture gMouseTexture;
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
#include "headers/Mouse.h"
#include "headers/Scoreboard.h"


int level = 0;
int n = 0,add=0;
bool quit = true;
Scores* scores;
Mouse mouse;
Ball ball;
Hole hole;
SDL_Event event;
LTimer stepTimer;
Tile* tileSet[TOTAL_TILES], * tileSet1[TOTAL_TILES], * tileSet2[TOTAL_TILES];
SDL_Rect bounce[TOTAL_TILES];
int state = 0; //0 = titleScreen, 1 = transition, 2 = game, 3 = endScreen
SDL_Color black = { 0,0,0 };
SDL_Color white = { 0xFF,0xFF,0xFF };

TTF_Font* gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 20);
TTF_Font* gTitleFont = TTF_OpenFont("fonts/pixelFont.ttf", 40);

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
void highScore();
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
	TTF_CloseFont(gPlayFont);
	TTF_CloseFont(gTitleFont);
	gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 20);
	gTitleFont = TTF_OpenFont("fonts/pixelFont.ttf", 40);
	bool success = true;
	gMouseTexture.addRenderer(gRenderer);
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
	if (!gMouseTexture.loadFromFile("pictures/tileset/68304.png")) {
		printf("Failed to load Mouse texture!\n");
		success = false;
	}
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
	if (!gTileTexture.loadFromFile("pictures/tileset/tilesetx.png"))
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
	n = 0;
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
		setTiles(tileSet, "headers/layer_background.csv");
		setTiles(tileSet1, "headers/layer_terrain.csv");
		setTiles(tileSet2, "headers/layer_obstacle.csv");
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//If the tile is a wall type tile
			if ((tileSet2[i]->getType() >= TILE_GREENROCK1) && (tileSet2[i]->getType() <= TILE_GREENWOOD) || (tileSet2[i]->getType() >= TILE_SANDROCK1) && (tileSet2[i]->getType() <= TILE_SANDWOOD) || (tileSet2[i]->getType() >= TILE_WATERROCK1) && (tileSet2[i]->getType() <= TILE_WATERWOOD))
			{
				bounce[n] = tileSet2[i]->getBox();
				n++;
			}
		}
		break;
	case 1:
		ball.setNewPos(SCREEN_WIDTH / 2+200, SCREEN_HEIGHT / 2+200);
		setTiles(tileSet, "headers/layer_background.csv");
		setTiles(tileSet1, "headers/layer_terrain.csv");
		setTiles(tileSet2, "headers/layer_obstacle2.csv");
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//If the tile is a wall type tile
			if ((tileSet2[i]->getType() >= TILE_GREENROCK1) && (tileSet2[i]->getType() <= TILE_GREENWOOD) || (tileSet2[i]->getType() >= TILE_SANDROCK1) && (tileSet2[i]->getType() <= TILE_SANDWOOD) || (tileSet2[i]->getType() >= TILE_WATERROCK1) && (tileSet2[i]->getType() <= TILE_WATERWOOD))
			{
				bounce[n] = tileSet2[i]->getBox();
				n++;
			}
		}
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
	mouse.handleEvent();
	float timeStep = stepTimer.getTicks() / 1000.f;
	ball.move(timeStep, bounce, n);
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
		tileSet1[i]->render();
		tileSet2[i]->render();
	}

	gHoleTexture.render((int)hole.getHoleX(), (int)hole.getHoleY(), hole.HOLE_WIDTH, hole.HOLE_HEIGHT);

	if (ball.Inside()) gGlowTexture.render(ball.getPosX() - (ball.BUTTON_WIDTH / 2 - 10), ball.getPosY() - (ball.BUTTON_HEIGHT / 2 - 10), ball.BUTTON_WIDTH, ball.BUTTON_HEIGHT);

	if (ball.getPoint()) gPointTexture.render(ball.getPosX() - (15 / 2 - 10), ball.getPosY() - (53 / 2 - 10), 15, 53, ball.getDegree());

	gBallTexture.render(ball.getPosX(), ball.getPosY(), ball.BALL_WIDTH, ball.BALL_HEIGHT);

	//gHitCount.render(100, 100);
	renderHitCount();

	gMouseTexture.render(mouse.getPosX(), mouse.getPosY(), mouse.MOUSE_WIDTH, mouse.MOUSE_HEIGHT);

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
		
	}
	MenuScreenBG.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	renderTransition();
	SDL_Delay(1000);
	state++;
}

void highScore() {
	scores->topscores(&scores);
	if (add==0) scores->insertsort(&scores, ball.getHitCount());
	scores->save();
	int board[5];
	for (int i = 0; i < 5; i++)
		if(scores->getScore(i)!=-1)
			board[i] = scores->getScore(i);
	if (scores->count() > 0) {
		for (int i = 0; i < scores->count() && i < 5; i++) {
			TTF_CloseFont(gPlayFont);
			gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 25);
			std::string stringHitCount = std::to_string(1 + i) + ". . . . . . . ." + std::to_string(board[i]);
			gHitCount.loadFromRenderedText(stringHitCount, black, gPlayFont);
			gHitCount.render(230, 160 + i * 30);
		}
	}
	else {
		TTF_CloseFont(gPlayFont);
		gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 25);
		std::string stringHitCount = "NO RECORDS";
		gHitCount.loadFromRenderedText(stringHitCount, black, gPlayFont);
		gHitCount.render(220, 160);
	}
	scores->deletelist(&scores);
	add++;
}

void endScreen() {
	TTF_CloseFont(gPlayFont);
	gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 25);
	std::string stringHitCount = "FINAL SCORE: " + std::to_string(ball.getHitCount());
	gHitCount.loadFromRenderedText(stringHitCount, black, gPlayFont);
	
	MenuScreenBG.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	gEndScreenTitle.render(200, 50);
	gEndScreenPlayAgain.render(100, 340);
	gHitCount.render(190, 120);
	highScore();

	SDL_RenderPresent(gRenderer);
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			
			quit = true;
		}
		
		
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym != SDLK_DELETE){
				Mix_PlayChannel(-1, gSFXHole, 0);
				level = 0;
				state = 1;
				add = 0;
				ball.resetcount();
			}
			else if (event.key.keysym.sym == SDLK_DELETE) {
				scores->save(); // reset scoreboard
			}
		}


	}
	

	return;
}

void renderHitCount() {
	//TTF_Font* gTitleFont = TTF_OpenFont("fonts/pixelFont.ttf", 40);
	TTF_CloseFont(gPlayFont);
	gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 20);
	std::string stringHitCount = "HIT COUNT: " + std::to_string(ball.getHitCount());
	gHitCount.loadFromRenderedText(stringHitCount, black, gPlayFont);
	gHitCount.render(10, 10);
}


void game()
{
	SDL_ShowCursor(false);
	if (state == 0)
	{
		titleScreen();
	}
	else if (state == 1) {
		transitionScreen();
	}
	else if (state==2)
	{
		graphics();
		update();
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





