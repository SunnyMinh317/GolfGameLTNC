#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

#include "Texture.h"
#include "Timer.h"

LTexture gTileTexture;
LTexture gBallTexture;
LTexture gHoleTexture;
LTexture gGlowTexture;
LTexture gPointTexture;

#include "Ball.h"
#include "Hole.h"
#include "Tile.h"

