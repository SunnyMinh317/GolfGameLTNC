#pragma once
#pragma once
#include <SDL_rect.h>
#include <fstream>
#include <string>
#include "Ball.h"

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = 300; //20x15
const int TOTAL_TILE_SPRITES = 4;

//Tile sprites & tile type
const int TILE_DARKBG = 0;
const int TILE_LIGHTBG = 1;
const int TILE_LIGHT = 2;
const int TILE_DARK = 3;

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
	std::ifstream map(s.c_str());

	//If the map couldn't be loaded
	if (map.fail())
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
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
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
			gTileClips[TILE_DARKBG].x = 0;
			gTileClips[TILE_DARKBG].y = 0;
			gTileClips[TILE_DARKBG].w = TILE_WIDTH;
			gTileClips[TILE_DARKBG].h = TILE_HEIGHT;

			gTileClips[TILE_LIGHTBG].x = 0;
			gTileClips[TILE_LIGHTBG].y = 32;
			gTileClips[TILE_LIGHTBG].w = TILE_WIDTH;
			gTileClips[TILE_LIGHTBG].h = TILE_HEIGHT;

			gTileClips[TILE_LIGHT].x = 32;
			gTileClips[TILE_LIGHT].y = 0;
			gTileClips[TILE_LIGHT].w = TILE_WIDTH;
			gTileClips[TILE_LIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_DARK].x = 32;
			gTileClips[TILE_DARK].y = 32;
			gTileClips[TILE_DARK].w = TILE_WIDTH;
			gTileClips[TILE_DARK].h = TILE_HEIGHT;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

