#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <vector>
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

Mix_Music* gSFXBGMusic = NULL;
Mix_Chunk* gSFXPressPlay = NULL;
Mix_Chunk* gSFXHole = NULL;
Mix_Chunk* gSFXLevelUp = NULL;
Mix_Chunk* gSFXPlayerName = NULL;

LTexture gMouseTexture;
LTexture gTileTexture;
LTexture gBallTexture;
LTexture gHoleTexture;
LTexture gGlowTexture;
LTexture gPointTexture;
LTexture gTitleMenu;
LTexture gPlayMenu;
LTexture Entername;
LTexture Playername;
LTexture gHitCount;
LTexture MenuScreenBG;
LTexture gEndScreenTitle;
LTexture gEndScreenPlayAgain;
LTexture gLevelNumber;
LTexture gPowerBar_overlay, gPowerBar_background, gPowerBar_power;

#include "headers/Ball.h"
#include "headers/Hole.h"
#include "headers/Tile.h"
#include "headers/Mouse.h"
#include "headers/Scoreboard.h"

SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

int level = 0;
int add = 0;
bool quit = true;
Scores* scores;
std::string name = "";
Mouse mouse;
Ball ball;
Hole hole;
SDL_Event event;
LTimer stepTimer;
Tile* tileSet[TOTAL_TILES], * tileSet1[TOTAL_TILES], * tileSet2[TOTAL_TILES], * tileSet3[TOTAL_TILES], tile;
std::vector<SDL_Rect> bounce, sand, water;
int state = 0; //0 = titleScreen, 1 = transition, 2 = game, 3 = endScreen
SDL_Color black = { 0,0,0 };
SDL_Color white = { 0xFF,0xFF,0xFF };

TTF_Font* gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 20);
TTF_Font* gTitleFont = TTF_OpenFont("fonts/pixelFont.ttf", 40);
TTF_Font* gHighScoresFont = TTF_OpenFont("fonts/name.ttf", 30);

bool init();
bool loadMedia();
void close();
void loadLevel(int level);
void update();
void game();
void graphics();
void titleScreen();
void transitionScreen();
void endScreen();
void highScore();

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
	bool success = true;
	TTF_CloseFont(gPlayFont);
	TTF_CloseFont(gTitleFont);
	gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 20);
	gTitleFont = TTF_OpenFont("fonts/pixelFont.ttf", 40);
	gPowerBar_overlay.addRenderer(gRenderer);
	gPowerBar_background.addRenderer(gRenderer);
	gPowerBar_power.addRenderer(gRenderer);
	gMouseTexture.addRenderer(gRenderer);
	gPointTexture.addRenderer(gRenderer);
	gBallTexture.addRenderer(gRenderer);
	gGlowTexture.addRenderer(gRenderer);
	gHoleTexture.addRenderer(gRenderer);
	gTileTexture.addRenderer(gRenderer);
	MenuScreenBG.addRenderer(gRenderer);
	gPlayMenu.addRenderer(gRenderer);
	gTitleMenu.addRenderer(gRenderer);
	Entername.addRenderer(gRenderer);
	Playername.addRenderer(gRenderer);
	gHitCount.addRenderer(gRenderer);
	gEndScreenTitle.addRenderer(gRenderer);
	gEndScreenPlayAgain.addRenderer(gRenderer);
	gLevelNumber.addRenderer(gRenderer);
	if (!gPowerBar_overlay.loadFromFile("resources/pictures/powermeter_overlay.png")) {
		printf("Failed to load Power bar texture!\n");
		success = false;
	}
	if (!gPowerBar_background.loadFromFile("resources/pictures/powermeter_background.png")) {
		printf("Failed to load Power bar texture!\n");
		success = false;
	}
	if (!gPowerBar_power.loadFromFile("resources/pictures/powermeter_power.png")) {
		printf("Failed to load Power bar texture!\n");
		success = false;
	}
	if (!gMouseTexture.loadFromFile("resources/pictures/tileset/68304.png")) {
		printf("Failed to load Mouse texture!\n");
		success = false;
	}
	if (!gPointTexture.loadFromFile("resources/pictures/point.png"))
	{
		printf("Failed to load Point texture!\n");
		success = false;
	}
	if (!gBallTexture.loadFromFile("resources/pictures/tileset/Golfball.png"))
	{
		printf("Failed to load Ball texture!\n");
		success = false;
	}
	if (!gGlowTexture.loadFromFile("resources/pictures/GolfGlow.png")) {
		printf("Failed to load Glow texture!\n");
		success = false;
	}
	if (!gHoleTexture.loadFromFile("resources/pictures/hole2.png"))
	{
		printf("Failed to load Hole texture!\n");
		success = false;
	}
	if (!gTileTexture.loadFromFile("resources/pictures/tileset/tilesetx.png"))
	{
		printf("Failed to load Hole texture!\n");
		success = false;
	}
	if (!MenuScreenBG.loadFromFile("resources/pictures/menuScreenBG.jpg"))
	{
		printf("Failed to load menu screen BG!\n");
		success = false;
	}
	if (gTitleFont == NULL) {
		std::cout << "Failed to load lazy font! SDL_ttf Error: %s\n" << TTF_GetError() << std::endl;
	}
	else {

		gTitleMenu.loadFromRenderedText("MINI GOLF A++", black, gTitleFont);
		gPlayMenu.loadFromRenderedText("PRESS ENTER TO PLAY!", black, gPlayFont);
		gEndScreenTitle.loadFromRenderedText("YOU WON!", black, gTitleFont);
		gEndScreenPlayAgain.loadFromRenderedText("PRESS ANY KEY TO PLAY AGAIN!", black, gPlayFont);
		Entername.loadFromRenderedText("ENTER YOUR NAME", black, gPlayFont);
		Playername.loadFromRenderedText(name.c_str(), black, gPlayFont);


	}
	gSFXBGMusic = Mix_LoadMUS("resources/music/8bitBGMWav.wav");
	gSFXHole = Mix_LoadWAV("resources/music/InHole.wav");
	gSFXLevelUp = Mix_LoadWAV("resources/music/levelUp.wav");
	gSFXPlayerName = Mix_LoadWAV("resources/music/TextSFX.mp3");

	return success;
}



void loadLevel(int level)
{
	bounce.clear();
	sand.clear();
	water.clear();
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
		ball.setNewPos(60, 240);
		ball.setNewHolePos(113, 145);
		tile.setTiles(gTileClips, tileSet, "resources/map/NewMap/GolfGame_TileLayer1.csv");
		tile.setTiles(gTileClips, tileSet1, "resources/map/NewMap/GolfGame_Water.csv");
		tile.setTiles(gTileClips, tileSet2, "resources/map/NewMap/GolfGame_Sand.csv");
		tile.setTiles(gTileClips, tileSet3, "resources/map/NewMap/GolfGame_Collision.csv");
		break;
	case 1:
		ball.setNewPos(250, 450);
		ball.setNewHolePos(360, 445);
		tile.setTiles(gTileClips, tileSet, "resources/map/NewMap/GolfGameLVL2_TileLayer1.csv");
		tile.setTiles(gTileClips, tileSet1, "resources/map/NewMap/GolfGameLVL2_Water.csv");
		tile.setTiles(gTileClips, tileSet2, "resources/map/NewMap/GolfGameLVL2_Sand.csv");
		tile.setTiles(gTileClips, tileSet3, "resources/map/NewMap/GolfGameLVL2_Collision.csv");
		break;
	}
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		if ((tileSet3[i]->getType() >= TILE_GREENROCK1) && (tileSet3[i]->getType() <= TILE_GREENWOOD) || (tileSet3[i]->getType() >= TILE_SANDROCK1) && (tileSet3[i]->getType() <= TILE_SANDWOOD) || (tileSet3[i]->getType() >= TILE_WATERROCK1) && (tileSet3[i]->getType() <= TILE_WATERWOOD))
		{
			bounce.push_back(tileSet3[i]->getBox());
		}
		//If the tile is a WATER type tile
		if (tileSet1[i]->getType() == TILE_WATERMIDDLE)
		{
			SDL_Rect waterBox = tileSet1[i]->getBox();
			water.push_back(waterBox);
		}
		//If the tile is a SAND type tile
		if (tileSet2[i]->getType() == TILE_SANDMIDDLE)
		{
			SDL_Rect sandBox = tileSet2[i]->getBox();
			sandBox.x -= TILE_WIDTH / 4;
			sandBox.y -= TILE_WIDTH / 4;
			sandBox.w += TILE_WIDTH / 2;
			sandBox.h += TILE_WIDTH / 2;

			sand.push_back(sandBox);
		}
	}

}


void update()
{

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			quit = true;
		}
		ball.handleEvent(event);
	}
	mouse.handleEvent();
	float timeStep = stepTimer.getTicks() / 1000.f;
	ball.move(timeStep, bounce, sand, water);
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
		gTileTexture.render(tileSet[i]->getBox().x, tileSet[i]->getBox().y, &gTileClips[tileSet[i]->getType()]);
		gTileTexture.render(tileSet1[i]->getBox().x, tileSet1[i]->getBox().y, &gTileClips[tileSet1[i]->getType()]);
		gTileTexture.render(tileSet2[i]->getBox().x, tileSet2[i]->getBox().y, &gTileClips[tileSet2[i]->getType()]);
		gTileTexture.render(tileSet3[i]->getBox().x, tileSet3[i]->getBox().y, &gTileClips[tileSet3[i]->getType()]);
	}

	gHoleTexture.render((int)ball.getHoleX(), (int)ball.getHoleY(), ball.HOLE_WIDTH, ball.HOLE_HEIGHT);

	if (ball.Inside()) gGlowTexture.render(ball.getPosX() - (ball.BUTTON_WIDTH / 2 - 10), ball.getPosY() - (ball.BUTTON_HEIGHT / 2 - 10), ball.BUTTON_WIDTH, ball.BUTTON_HEIGHT);

	if (ball.getPoint()) {
		gPointTexture.render(ball.getPosX() - (15 / 2 - 10), ball.getPosY() - (53 / 2 - 10), 15, 53, ball.getDegree());
		if (ball.getPosX() <= SCREEN_WIDTH / 2 && ball.getPosY() <= SCREEN_HEIGHT / 2) {
			gPowerBar_background.render(ball.getPosX() + 40, ball.getPosY() + 40, 12, 48);
			gPowerBar_power.render(ball.getPosX() + 43, ball.getPosY() + 43 + 42 * (1 - ball.getPercent()), 6, 42 * ball.getPercent());
			gPowerBar_overlay.render(ball.getPosX() + 40, ball.getPosY() + 40, 12, 48);
		}
		else if (ball.getPosX() < SCREEN_WIDTH / 2 && ball.getPosY() > SCREEN_HEIGHT / 2) {
			gPowerBar_background.render(ball.getPosX() + 40, ball.getPosY() - 40, 12, 48);
			gPowerBar_power.render(ball.getPosX() + 43, ball.getPosY() - 37 + 42 * (1 - ball.getPercent()), 6, 42 * ball.getPercent());
			gPowerBar_overlay.render(ball.getPosX() + 40, ball.getPosY() - 40, 12, 48);
		}
		else if (ball.getPosX() > SCREEN_WIDTH / 2 && ball.getPosY() < SCREEN_HEIGHT / 2) {
			gPowerBar_background.render(ball.getPosX() - 40, ball.getPosY() + 40, 12, 48);
			gPowerBar_power.render(ball.getPosX() - 37, ball.getPosY() + 43 + 42 * (1 - ball.getPercent()), 6, 42 * ball.getPercent());
			gPowerBar_overlay.render(ball.getPosX() - 40, ball.getPosY() + 40, 12, 48);
		}
		else if (ball.getPosX() > SCREEN_WIDTH / 2 && ball.getPosY() > SCREEN_HEIGHT / 2) {
			gPowerBar_background.render(ball.getPosX() - 40, ball.getPosY() - 40, 12, 48);
			gPowerBar_power.render(ball.getPosX() - 37, ball.getPosY() - 37 + 42 * (1 - ball.getPercent()), 6, 42 * ball.getPercent());
			gPowerBar_overlay.render(ball.getPosX() - 40, ball.getPosY() - 40, 12, 48);
		}
	}


	gBallTexture.render(ball.getPosX(), ball.getPosY(), ball.BALL_WIDTH, ball.BALL_HEIGHT);

	TTF_CloseFont(gPlayFont);
	gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 20);
	std::string stringHitCount = "HIT COUNT: " + std::to_string(ball.getHitCount());
	gHitCount.loadFromRenderedText(stringHitCount, black, gPlayFont);
	gHitCount.render(10, 10);

	gMouseTexture.render(mouse.getPosX(), mouse.getPosY(), mouse.MOUSE_WIDTH, mouse.MOUSE_HEIGHT);

	SDL_RenderPresent(gRenderer);
}

void titleScreen() {
	SDL_StartTextInput();
	bool renderText = true;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			quit = true;
		}

		MenuScreenBG.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		gTitleMenu.render(140, 150);
		gPlayMenu.render(170, 340);
		Entername.render(200, 230);
		Playername.render(320 - name.substr(0, 12).length() * 8, 270);

		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_BACKSPACE && name.length() > 0)
			{
				name.pop_back();
				Mix_PlayChannel(-1, gSFXPlayerName, 0);
				renderText = true;
			}
			else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
			{
				SDL_SetClipboardText(name.c_str());
			}
			else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
			{
				name = SDL_GetClipboardText();
				renderText = true;
			}
			else if (event.key.keysym.sym == 13 && name != "") {
				for (int i = 0; i < name.length(); i++) {
					if (name[i] != ' ') {
						Mix_PlayChannel(-1, gSFXHole, 0);
						state++;
						break;
					}
				}
			}
		}
		else if (event.type == SDL_TEXTINPUT)
		{
			if (!(SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' || event.text.text[0] == 'v' || event.text.text[0] == 'V')))
			{
				if (event.text.text[0] != ' ') {
					name += event.text.text;
					Mix_PlayChannel(-1, gSFXPlayerName, 0);
					renderText = true;
				}
			}
		}
	}
	if (renderText)
	{
		TTF_CloseFont(gPlayFont);
		gPlayFont = TTF_OpenFont("fonts/pixelFont.ttf", 20);
		//Text is not empty
		if (name != "")
		{
			//Render new text

			Playername.loadFromRenderedText(name.substr(0, 12).c_str(), black, gPlayFont);
		}
		//Text is empty
		else
		{
			//Render space texture
			Playername.loadFromRenderedText(" ", black, gPlayFont);
		}
	}
	SDL_RenderPresent(gRenderer);
	SDL_StopTextInput();
	return;
}

void transitionScreen() {
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			quit = true;
		}
	}
	Mix_PlayChannel(-1, gSFXLevelUp, 0);
	TTF_Font* gTitleFont = TTF_OpenFont("fonts/pixelFont.ttf", 40);
	std::cout << "LEVEL = " << std::to_string(level + 1) << std::endl;
	gLevelNumber.loadFromRenderedText("LEVEL " + std::to_string(level + 1), black, gTitleFont);
	MenuScreenBG.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	gLevelNumber.render(SCREEN_HEIGHT / 2 - 30, SCREEN_WIDTH / 2);
	SDL_RenderPresent(gRenderer);
	SDL_Delay(1000);
	state++;
}

void highScore() {
	scores->topscores(&scores);
	if (add == 0) scores->insertsort(&scores, ball.getHitCount(), name.substr(0, 10));
	scores->save();
	Scores* board[5];
	for (int i = 0; i < 5; i++)
		if (scores->getScore(i)->getdata() != -1)
			board[i] = scores->getScore(i);
	if (scores->count() > 0) {
		for (int i = 0; i < scores->count() && i < 5; i++) {
			TTF_CloseFont(gHighScoresFont);
			gHighScoresFont = TTF_OpenFont("fonts/name.ttf", 30);
			std::string stringHitCount = board[i]->getname().substr(0, 10);
			gHitCount.loadFromRenderedText(stringHitCount, black, gHighScoresFont);
			gHitCount.render(270 - stringHitCount.length() * 14, 160 + i * 30);
			stringHitCount = ". . . . . . . . . " + std::to_string(board[i]->getdata());
			gHitCount.loadFromRenderedText(stringHitCount, black, gHighScoresFont);
			gHitCount.render(280, 160 + i * 30);
		}
	}
	else {
		TTF_CloseFont(gHighScoresFont);
		gHighScoresFont = TTF_OpenFont("fonts/name.ttf", 40);
		std::string stringHitCount = "NO RECORDS";
		gHitCount.loadFromRenderedText(stringHitCount, black, gHighScoresFont);
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
			if (event.key.keysym.sym != SDLK_DELETE) {
				Mix_PlayChannel(-1, gSFXHole, 0);
				level = 0;
				state = 0;
				add = 0;
				name = "";
				ball.resetcount();
			}
			else if (event.key.keysym.sym == SDLK_DELETE) {
				scores->save(); // reset scoreboard
			}
		}
	}
	return;
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
	else if (state == 2)
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
			Mix_VolumeMusic(15);
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





