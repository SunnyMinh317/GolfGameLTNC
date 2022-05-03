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
	//Initializes position and type
	Tile(int x, int y, int tileType);

	//Show tile
	void render();

	//Get tile type
	int getType();

	//Get collision box
	SDL_Rect getBox();

private:
	//Tile attributes
	SDL_Rect mBox;

	//Tile Type
	int mType;
};

SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

Tile::Tile(int x, int y, int tileType)
{
	//Offsets
	mBox.x = x;
	mBox.y = y;

	//Set collision box
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	//Get tile type
	mType = tileType;
}

//LOI RENDER
void Tile::render()
{
	gTileTexture.render((int)mBox.x, (int)mBox.y, &gTileClips[mType]);
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}


bool setTiles(Tile* tiles[], std::string s)
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream csv(s.c_str());

	//If the map couldn't be loaded
	if (csv.fail())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			csv >> tileType;

			//If the was a problem in reading the map
			if (csv.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= -1) && (tileType < TOTAL_TILE_SPRITES))
			{
				if (tileType == -1) tileType = 54;
				tiles[i] = new Tile(x, y, tileType);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}
			//Move to next tile spot
			x += TILE_WIDTH;   

			//If we've gone too far
			if (x >= SCREEN_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
			
			
		}

		//Clip the sprite sheet
		if (tilesLoaded)
		{
			//GREEN
			gTileClips[TILE_GREENTOPLEFT].x = 2 * 0;
			gTileClips[TILE_GREENTOPLEFT].y = 2 * 0;
			gTileClips[TILE_GREENTOPLEFT].w = TILE_WIDTH;
			gTileClips[TILE_GREENTOPLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_GREENTOP].x = 2 * 16;
			gTileClips[TILE_GREENTOP].y = 2 * 0;
			gTileClips[TILE_GREENTOP].w = TILE_WIDTH;
			gTileClips[TILE_GREENTOP].h = TILE_HEIGHT;

			gTileClips[TILE_GREENTOPRIGHT].x = 2 * 32;
			gTileClips[TILE_GREENTOPRIGHT].y = 2 * 0;
			gTileClips[TILE_GREENTOPRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_GREENTOPRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_GREENLEFT].x = 2 * 0;
			gTileClips[TILE_GREENLEFT].y = 2 * 16;
			gTileClips[TILE_GREENLEFT].w = TILE_WIDTH;
			gTileClips[TILE_GREENLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_GREENMIDDLE].x = 2 * 16;
			gTileClips[TILE_GREENMIDDLE].y = 2 * 16;
			gTileClips[TILE_GREENMIDDLE].w = TILE_WIDTH;
			gTileClips[TILE_GREENMIDDLE].h = TILE_HEIGHT;

			gTileClips[TILE_GREENRIGHT].x = 2 * 32;
			gTileClips[TILE_GREENRIGHT].y = 2 * 16;
			gTileClips[TILE_GREENRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_GREENRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_GREENBOTLEFT].x = 2 * 0;
			gTileClips[TILE_GREENBOTLEFT].y = 2 * 32;
			gTileClips[TILE_GREENBOTLEFT].w = TILE_WIDTH;
			gTileClips[TILE_GREENBOTLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_GREENBOT].x = 2 * 16;
			gTileClips[TILE_GREENBOT].y = 2 * 32;
			gTileClips[TILE_GREENBOT].w = TILE_WIDTH;
			gTileClips[TILE_GREENBOT].h = TILE_HEIGHT;

			gTileClips[TILE_GREENBOTRIGHT].x = 2 * 32;
			gTileClips[TILE_GREENBOTRIGHT].y = 2 * 32;
			gTileClips[TILE_GREENBOTRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_GREENBOTRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_GREENSUPTOPLEFT].x = 2 * 48;
			gTileClips[TILE_GREENSUPTOPLEFT].y = 2 * 0;
			gTileClips[TILE_GREENSUPTOPLEFT].w = TILE_WIDTH;
			gTileClips[TILE_GREENSUPTOPLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_GREENSUPTOPRIGHT].x = 2 * 64;
			gTileClips[TILE_GREENSUPTOPRIGHT].y = 2 * 0;
			gTileClips[TILE_GREENSUPTOPRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_GREENSUPTOPRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_GREENSUPBOTLEFT].x = 2 * 48;
			gTileClips[TILE_GREENSUPBOTLEFT].y = 2 * 16;
			gTileClips[TILE_GREENSUPBOTLEFT].w = TILE_WIDTH;
			gTileClips[TILE_GREENSUPBOTLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_GREENSUPBOTRIGHT].x = 2 * 64;
			gTileClips[TILE_GREENSUPBOTRIGHT].y = 2 * 16;
			gTileClips[TILE_GREENSUPBOTRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_GREENSUPBOTRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_FLOWER1].x = 2 * 80;
			gTileClips[TILE_FLOWER1].y = 2 * 0;
			gTileClips[TILE_FLOWER1].w = TILE_WIDTH;
			gTileClips[TILE_FLOWER1].h = TILE_HEIGHT;

			gTileClips[TILE_FLOWER2].x = 2 * 80;
			gTileClips[TILE_FLOWER2].y = 2 * 16;
			gTileClips[TILE_FLOWER2].w = TILE_WIDTH;
			gTileClips[TILE_FLOWER2].h = TILE_HEIGHT;

			gTileClips[TILE_GREENROCK1].x = 2 * 48;
			gTileClips[TILE_GREENROCK1].y = 2 * 32;
			gTileClips[TILE_GREENROCK1].w = TILE_WIDTH;
			gTileClips[TILE_GREENROCK1].h = TILE_HEIGHT;

			gTileClips[TILE_GREENROCK2].x = 2 * 64;
			gTileClips[TILE_GREENROCK2].y = 2 * 32;
			gTileClips[TILE_GREENROCK2].w = TILE_WIDTH;
			gTileClips[TILE_GREENROCK2].h = TILE_HEIGHT;

			gTileClips[TILE_GREENWOOD].x = 2 * 80;
			gTileClips[TILE_GREENWOOD].y = 2 * 32;
			gTileClips[TILE_GREENWOOD].w = TILE_WIDTH;
			gTileClips[TILE_GREENWOOD].h = TILE_HEIGHT;

			//SAND
			gTileClips[TILE_SANDTOPLEFT].x = 2 * 0;
			gTileClips[TILE_SANDTOPLEFT].y = 2 * 48;
			gTileClips[TILE_SANDTOPLEFT].w = TILE_WIDTH;
			gTileClips[TILE_SANDTOPLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_SANDTOP].x = 2 * 16;
			gTileClips[TILE_SANDTOP].y = 2 * 48;
			gTileClips[TILE_SANDTOP].w = TILE_WIDTH;
			gTileClips[TILE_SANDTOP].h = TILE_HEIGHT;

			gTileClips[TILE_SANDTOPRIGHT].x = 2 * 32;
			gTileClips[TILE_SANDTOPRIGHT].y = 2 * 48;
			gTileClips[TILE_SANDTOPRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_SANDTOPRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_SANDLEFT].x = 2 * 0;
			gTileClips[TILE_SANDLEFT].y = 2 * 64;
			gTileClips[TILE_SANDLEFT].w = TILE_WIDTH;
			gTileClips[TILE_SANDLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_SANDMIDDLE].x = 2 * 16;
			gTileClips[TILE_SANDMIDDLE].y = 2 * 64;
			gTileClips[TILE_SANDMIDDLE].w = TILE_WIDTH;
			gTileClips[TILE_SANDMIDDLE].h = TILE_HEIGHT;

			gTileClips[TILE_SANDRIGHT].x = 2 * 32;
			gTileClips[TILE_SANDRIGHT].y = 2 * 64;
			gTileClips[TILE_SANDRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_SANDRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_SANDBOTLEFT].x = 2 * 0;
			gTileClips[TILE_SANDBOTLEFT].y = 2 * 80;
			gTileClips[TILE_SANDBOTLEFT].w = TILE_WIDTH;
			gTileClips[TILE_SANDBOTLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_SANDBOT].x = 2 * 16;
			gTileClips[TILE_SANDBOT].y = 2 * 80;
			gTileClips[TILE_SANDBOT].w = TILE_WIDTH;
			gTileClips[TILE_SANDBOT].h = TILE_HEIGHT;

			gTileClips[TILE_SANDBOTRIGHT].x = 2 * 32;
			gTileClips[TILE_SANDBOTRIGHT].y = 2 * 80;
			gTileClips[TILE_SANDBOTRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_SANDBOTRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_SANDSUPTOPLEFT].x = 2 * 48;
			gTileClips[TILE_SANDSUPTOPLEFT].y = 2 * 48;
			gTileClips[TILE_SANDSUPTOPLEFT].w = TILE_WIDTH;
			gTileClips[TILE_SANDSUPTOPLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_SANDSUPTOPRIGHT].x = 2 * 64;
			gTileClips[TILE_SANDSUPTOPRIGHT].y = 2 * 48;
			gTileClips[TILE_SANDSUPTOPRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_SANDSUPTOPRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_SANDSUPBOTLEFT].x = 2 * 48;
			gTileClips[TILE_SANDSUPBOTLEFT].y = 2 * 64;
			gTileClips[TILE_SANDSUPBOTLEFT].w = TILE_WIDTH;
			gTileClips[TILE_SANDSUPBOTLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_SANDSUPBOTRIGHT].x = 2 * 64;
			gTileClips[TILE_SANDSUPBOTRIGHT].y = 2 * 64;
			gTileClips[TILE_SANDSUPBOTRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_SANDSUPBOTRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_SANDDECOR1].x = 2 * 80;
			gTileClips[TILE_SANDDECOR1].y = 2 * 48;
			gTileClips[TILE_SANDDECOR1].w = TILE_WIDTH;
			gTileClips[TILE_SANDDECOR1].h = TILE_HEIGHT;

			gTileClips[TILE_SANDDECOR2].x = 2 * 80;
			gTileClips[TILE_SANDDECOR2].y = 2 * 64;
			gTileClips[TILE_SANDDECOR2].w = TILE_WIDTH;
			gTileClips[TILE_SANDDECOR2].h = TILE_HEIGHT;

			gTileClips[TILE_SANDROCK1].x = 2 * 48;
			gTileClips[TILE_SANDROCK1].y = 2 * 80;
			gTileClips[TILE_SANDROCK1].w = TILE_WIDTH;
			gTileClips[TILE_SANDROCK1].h = TILE_HEIGHT;

			gTileClips[TILE_SANDROCK2].x = 2 * 64;
			gTileClips[TILE_SANDROCK2].y = 2 * 80;
			gTileClips[TILE_SANDROCK2].w = TILE_WIDTH;
			gTileClips[TILE_SANDROCK2].h = TILE_HEIGHT;

			gTileClips[TILE_SANDWOOD].x = 2 * 80;
			gTileClips[TILE_SANDWOOD].y = 2 * 80;
			gTileClips[TILE_SANDWOOD].w = TILE_WIDTH;
			gTileClips[TILE_SANDWOOD].h = TILE_HEIGHT;

			//WATER
			gTileClips[TILE_WATERTOPLEFT].x = 2 * 0;
			gTileClips[TILE_WATERTOPLEFT].y = 2 * 96;
			gTileClips[TILE_WATERTOPLEFT].w = TILE_WIDTH;
			gTileClips[TILE_WATERTOPLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_WATERTOP].x = 2 * 16;
			gTileClips[TILE_WATERTOP].y = 2 * 96;
			gTileClips[TILE_WATERTOP].w = TILE_WIDTH;
			gTileClips[TILE_WATERTOP].h = TILE_HEIGHT;

			gTileClips[TILE_WATERTOPRIGHT].x = 2 * 32;
			gTileClips[TILE_WATERTOPRIGHT].y = 2 * 96;
			gTileClips[TILE_WATERTOPRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_WATERTOPRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_WATERLEFT].x = 2 * 0;
			gTileClips[TILE_WATERLEFT].y = 2 * 112;
			gTileClips[TILE_WATERLEFT].w = TILE_WIDTH;
			gTileClips[TILE_WATERLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_WATERMIDDLE].x = 2 * 16;
			gTileClips[TILE_WATERMIDDLE].y = 2 * 112;
			gTileClips[TILE_WATERMIDDLE].w = TILE_WIDTH;
			gTileClips[TILE_WATERMIDDLE].h = TILE_HEIGHT;

			gTileClips[TILE_WATERRIGHT].x = 2 * 32;
			gTileClips[TILE_WATERRIGHT].y = 2 * 112;
			gTileClips[TILE_WATERRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_WATERRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_WATERBOTLEFT].x = 2 * 0;
			gTileClips[TILE_WATERBOTLEFT].y = 2 * 128;
			gTileClips[TILE_WATERBOTLEFT].w = TILE_WIDTH;
			gTileClips[TILE_WATERBOTLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_WATERBOT].x = 2 * 16;
			gTileClips[TILE_WATERBOT].y = 2 * 128;
			gTileClips[TILE_WATERBOT].w = TILE_WIDTH;
			gTileClips[TILE_WATERBOT].h = TILE_HEIGHT;

			gTileClips[TILE_WATERBOTRIGHT].x = 2 * 32;
			gTileClips[TILE_WATERBOTRIGHT].y = 2 * 128;
			gTileClips[TILE_WATERBOTRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_WATERBOTRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_WATERSUPTOPLEFT].x = 2 * 48;
			gTileClips[TILE_WATERSUPTOPLEFT].y = 2 * 48;
			gTileClips[TILE_WATERSUPTOPLEFT].w = TILE_WIDTH;
			gTileClips[TILE_WATERSUPTOPLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_WATERSUPTOPRIGHT].x = 2 * 64;
			gTileClips[TILE_WATERSUPTOPRIGHT].y = 2 * 96;
			gTileClips[TILE_WATERSUPTOPRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_WATERSUPTOPRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_WATERSUPBOTLEFT].x = 2 * 48;
			gTileClips[TILE_WATERSUPBOTLEFT].y = 2 * 112;
			gTileClips[TILE_WATERSUPBOTLEFT].w = TILE_WIDTH;
			gTileClips[TILE_WATERSUPBOTLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_WATERSUPBOTRIGHT].x = 2 * 64;
			gTileClips[TILE_WATERSUPBOTRIGHT].y = 2 * 112;
			gTileClips[TILE_WATERSUPBOTRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_WATERSUPBOTRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_WATERFLOWER1].x = 2 * 80;
			gTileClips[TILE_WATERFLOWER1].y = 2 * 96;
			gTileClips[TILE_WATERFLOWER1].w = TILE_WIDTH;
			gTileClips[TILE_WATERFLOWER1].h = TILE_HEIGHT;

			gTileClips[TILE_WATERFLOWER2].x = 2 * 80;
			gTileClips[TILE_WATERFLOWER2].y = 2 * 112;
			gTileClips[TILE_WATERFLOWER2].w = TILE_WIDTH;
			gTileClips[TILE_WATERFLOWER2].h = TILE_HEIGHT;

			gTileClips[TILE_WATERROCK1].x = 2 * 48;
			gTileClips[TILE_WATERROCK1].y = 2 * 128;
			gTileClips[TILE_WATERROCK1].w = TILE_WIDTH;
			gTileClips[TILE_WATERROCK1].h = TILE_HEIGHT;

			gTileClips[TILE_WATERROCK2].x = 2 * 64;
			gTileClips[TILE_WATERROCK2].y = 2 * 128;
			gTileClips[TILE_WATERROCK2].w = TILE_WIDTH;
			gTileClips[TILE_WATERROCK2].h = TILE_HEIGHT;

			gTileClips[TILE_WATERWOOD].x = 2 * 80;
			gTileClips[TILE_WATERWOOD].y = 2 * 128;
			gTileClips[TILE_WATERWOOD].w = TILE_WIDTH;
			gTileClips[TILE_WATERWOOD].h = TILE_HEIGHT;

			gTileClips[54] = { 0,0,0,0 };
		}
	}

	//Close the file
	csv.close();

	//If the map was loaded fine
	return tilesLoaded;
}

