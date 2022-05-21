#pragma once
#pragma once
#include <SDL_rect.h>
#include <fstream>
#include <string>
#include "Ball.h"

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = 20 * 15; //40x30
const int TOTAL_TILE_SPRITES = 55; //6x9

//Tile sprites & tile type
const int TILE_GREENTOPLEFT = 0;
const int TILE_GREENTOP = 1;
const int TILE_GREENTOPRIGHT = 2;
const int TILE_GREENLEFT = 6;
const int TILE_GREENMIDDLE = 7;
const int TILE_GREENRIGHT = 8;
const int TILE_GREENBOTLEFT = 12;
const int TILE_GREENBOT = 13;
const int TILE_GREENBOTRIGHT = 14;

const int TILE_GREENSUPTOPLEFT = 3;
const int TILE_GREENSUPTOPRIGHT = 4;
const int TILE_GREENSUPBOTLEFT = 9;
const int TILE_GREENSUPBOTRIGHT = 10;

const int TILE_FLOWER1 = 5;
const int TILE_FLOWER2 = 11;
const int TILE_GREENROCK1 = 15;
const int TILE_GREENROCK2 = 16;
const int TILE_GREENWOOD = 17;

const int TILE_SANDTOPLEFT = 18;
const int TILE_SANDTOP = 19;
const int TILE_SANDTOPRIGHT = 20;
const int TILE_SANDLEFT = 24;
const int TILE_SANDMIDDLE = 25;
const int TILE_SANDRIGHT = 26;
const int TILE_SANDBOTLEFT = 30;
const int TILE_SANDBOT = 31;
const int TILE_SANDBOTRIGHT = 32;

const int TILE_SANDSUPTOPLEFT = 21;
const int TILE_SANDSUPTOPRIGHT = 22;
const int TILE_SANDSUPBOTLEFT = 27;
const int TILE_SANDSUPBOTRIGHT = 28;

const int TILE_SANDDECOR1 = 23;
const int TILE_SANDDECOR2 = 29;
const int TILE_SANDROCK1 = 33;
const int TILE_SANDROCK2 = 34;
const int TILE_SANDWOOD = 35;

const int TILE_WATERTOPLEFT = 36;
const int TILE_WATERTOP = 37;
const int TILE_WATERTOPRIGHT = 38;
const int TILE_WATERLEFT = 42;
const int TILE_WATERMIDDLE = 43;
const int TILE_WATERRIGHT = 44;
const int TILE_WATERBOTLEFT = 48;
const int TILE_WATERBOT = 49;
const int TILE_WATERBOTRIGHT = 50;

const int TILE_WATERSUPTOPLEFT = 39;
const int TILE_WATERSUPTOPRIGHT = 40;
const int TILE_WATERSUPBOTLEFT = 45;
const int TILE_WATERSUPBOTRIGHT = 46;

const int TILE_WATERFLOWER1 = 41;
const int TILE_WATERFLOWER2 = 47;
const int TILE_WATERROCK1 = 51;
const int TILE_WATERROCK2 = 52;
const int TILE_WATERWOOD = 53;



class Tile
{
public:
	Tile();

	//Initializes position and type
	Tile(int x, int y, int tileType);

	//Show tile
	void render();

	//Get tile type
	int getType();

	//Get collision box
	SDL_Rect getBox();

	SDL_Rect* getpBox();

	bool setTiles(SDL_Rect TileClips[], Tile* tiles[], std::string s);

private:
	//Tile attributes
	SDL_Rect mBox;

	//Tile Type
	int mType;
};