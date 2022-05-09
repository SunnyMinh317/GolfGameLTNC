#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "headers\Tile.h"


Tile::Tile()
{
	mBox.x = 0;
	mBox.y = 0;

	mBox.w = 0;
	mBox.h = 0;

	mType = 54;
}

Tile::Tile(int x, int y, int tileType)
{
	mBox.x = x;
	mBox.y = y;

	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	mType = tileType;
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}


bool Tile::setTiles(SDL_Rect TileClips[], Tile* tiles[], std::string s)
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
			if (x >= 640)
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
			TileClips[TILE_GREENTOPLEFT].x = 2 * 0;
			TileClips[TILE_GREENTOPLEFT].y = 2 * 0;
			TileClips[TILE_GREENTOPLEFT].w = TILE_WIDTH;
			TileClips[TILE_GREENTOPLEFT].h = TILE_HEIGHT;

			TileClips[TILE_GREENTOP].x = 2 * 16;
			TileClips[TILE_GREENTOP].y = 2 * 0;
			TileClips[TILE_GREENTOP].w = TILE_WIDTH;
			TileClips[TILE_GREENTOP].h = TILE_HEIGHT;

			TileClips[TILE_GREENTOPRIGHT].x = 2 * 32;
			TileClips[TILE_GREENTOPRIGHT].y = 2 * 0;
			TileClips[TILE_GREENTOPRIGHT].w = TILE_WIDTH;
			TileClips[TILE_GREENTOPRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_GREENLEFT].x = 2 * 0;
			TileClips[TILE_GREENLEFT].y = 2 * 16;
			TileClips[TILE_GREENLEFT].w = TILE_WIDTH;
			TileClips[TILE_GREENLEFT].h = TILE_HEIGHT;

			TileClips[TILE_GREENMIDDLE].x = 2 * 16;
			TileClips[TILE_GREENMIDDLE].y = 2 * 16;
			TileClips[TILE_GREENMIDDLE].w = TILE_WIDTH;
			TileClips[TILE_GREENMIDDLE].h = TILE_HEIGHT;

			TileClips[TILE_GREENRIGHT].x = 2 * 32;
			TileClips[TILE_GREENRIGHT].y = 2 * 16;
			TileClips[TILE_GREENRIGHT].w = TILE_WIDTH;
			TileClips[TILE_GREENRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_GREENBOTLEFT].x = 2 * 0;
			TileClips[TILE_GREENBOTLEFT].y = 2 * 32;
			TileClips[TILE_GREENBOTLEFT].w = TILE_WIDTH;
			TileClips[TILE_GREENBOTLEFT].h = TILE_HEIGHT;

			TileClips[TILE_GREENBOT].x = 2 * 16;
			TileClips[TILE_GREENBOT].y = 2 * 32;
			TileClips[TILE_GREENBOT].w = TILE_WIDTH;
			TileClips[TILE_GREENBOT].h = TILE_HEIGHT;

			TileClips[TILE_GREENBOTRIGHT].x = 2 * 32;
			TileClips[TILE_GREENBOTRIGHT].y = 2 * 32;
			TileClips[TILE_GREENBOTRIGHT].w = TILE_WIDTH;
			TileClips[TILE_GREENBOTRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_GREENSUPTOPLEFT].x = 2 * 48;
			TileClips[TILE_GREENSUPTOPLEFT].y = 2 * 0;
			TileClips[TILE_GREENSUPTOPLEFT].w = TILE_WIDTH;
			TileClips[TILE_GREENSUPTOPLEFT].h = TILE_HEIGHT;

			TileClips[TILE_GREENSUPTOPRIGHT].x = 2 * 64;
			TileClips[TILE_GREENSUPTOPRIGHT].y = 2 * 0;
			TileClips[TILE_GREENSUPTOPRIGHT].w = TILE_WIDTH;
			TileClips[TILE_GREENSUPTOPRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_GREENSUPBOTLEFT].x = 2 * 48;
			TileClips[TILE_GREENSUPBOTLEFT].y = 2 * 16;
			TileClips[TILE_GREENSUPBOTLEFT].w = TILE_WIDTH;
			TileClips[TILE_GREENSUPBOTLEFT].h = TILE_HEIGHT;

			TileClips[TILE_GREENSUPBOTRIGHT].x = 2 * 64;
			TileClips[TILE_GREENSUPBOTRIGHT].y = 2 * 16;
			TileClips[TILE_GREENSUPBOTRIGHT].w = TILE_WIDTH;
			TileClips[TILE_GREENSUPBOTRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_FLOWER1].x = 2 * 80;
			TileClips[TILE_FLOWER1].y = 2 * 0;
			TileClips[TILE_FLOWER1].w = TILE_WIDTH;
			TileClips[TILE_FLOWER1].h = TILE_HEIGHT;

			TileClips[TILE_FLOWER2].x = 2 * 80;
			TileClips[TILE_FLOWER2].y = 2 * 16;
			TileClips[TILE_FLOWER2].w = TILE_WIDTH;
			TileClips[TILE_FLOWER2].h = TILE_HEIGHT;

			TileClips[TILE_GREENROCK1].x = 2 * 48;
			TileClips[TILE_GREENROCK1].y = 2 * 32;
			TileClips[TILE_GREENROCK1].w = TILE_WIDTH;
			TileClips[TILE_GREENROCK1].h = TILE_HEIGHT;

			TileClips[TILE_GREENROCK2].x = 2 * 64;
			TileClips[TILE_GREENROCK2].y = 2 * 32;
			TileClips[TILE_GREENROCK2].w = TILE_WIDTH;
			TileClips[TILE_GREENROCK2].h = TILE_HEIGHT;

			TileClips[TILE_GREENWOOD].x = 2 * 80;
			TileClips[TILE_GREENWOOD].y = 2 * 32;
			TileClips[TILE_GREENWOOD].w = TILE_WIDTH;
			TileClips[TILE_GREENWOOD].h = TILE_HEIGHT;

			//SAND
			TileClips[TILE_SANDTOPLEFT].x = 2 * 0;
			TileClips[TILE_SANDTOPLEFT].y = 2 * 48;
			TileClips[TILE_SANDTOPLEFT].w = TILE_WIDTH;
			TileClips[TILE_SANDTOPLEFT].h = TILE_HEIGHT;

			TileClips[TILE_SANDTOP].x = 2 * 16;
			TileClips[TILE_SANDTOP].y = 2 * 48;
			TileClips[TILE_SANDTOP].w = TILE_WIDTH;
			TileClips[TILE_SANDTOP].h = TILE_HEIGHT;

			TileClips[TILE_SANDTOPRIGHT].x = 2 * 32;
			TileClips[TILE_SANDTOPRIGHT].y = 2 * 48;
			TileClips[TILE_SANDTOPRIGHT].w = TILE_WIDTH;
			TileClips[TILE_SANDTOPRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_SANDLEFT].x = 2 * 0;
			TileClips[TILE_SANDLEFT].y = 2 * 64;
			TileClips[TILE_SANDLEFT].w = TILE_WIDTH;
			TileClips[TILE_SANDLEFT].h = TILE_HEIGHT;

			TileClips[TILE_SANDMIDDLE].x = 2 * 16;
			TileClips[TILE_SANDMIDDLE].y = 2 * 64;
			TileClips[TILE_SANDMIDDLE].w = TILE_WIDTH;
			TileClips[TILE_SANDMIDDLE].h = TILE_HEIGHT;

			TileClips[TILE_SANDRIGHT].x = 2 * 32;
			TileClips[TILE_SANDRIGHT].y = 2 * 64;
			TileClips[TILE_SANDRIGHT].w = TILE_WIDTH;
			TileClips[TILE_SANDRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_SANDBOTLEFT].x = 2 * 0;
			TileClips[TILE_SANDBOTLEFT].y = 2 * 80;
			TileClips[TILE_SANDBOTLEFT].w = TILE_WIDTH;
			TileClips[TILE_SANDBOTLEFT].h = TILE_HEIGHT;

			TileClips[TILE_SANDBOT].x = 2 * 16;
			TileClips[TILE_SANDBOT].y = 2 * 80;
			TileClips[TILE_SANDBOT].w = TILE_WIDTH;
			TileClips[TILE_SANDBOT].h = TILE_HEIGHT;

			TileClips[TILE_SANDBOTRIGHT].x = 2 * 32;
			TileClips[TILE_SANDBOTRIGHT].y = 2 * 80;
			TileClips[TILE_SANDBOTRIGHT].w = TILE_WIDTH;
			TileClips[TILE_SANDBOTRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_SANDSUPTOPLEFT].x = 2 * 48;
			TileClips[TILE_SANDSUPTOPLEFT].y = 2 * 48;
			TileClips[TILE_SANDSUPTOPLEFT].w = TILE_WIDTH;
			TileClips[TILE_SANDSUPTOPLEFT].h = TILE_HEIGHT;

			TileClips[TILE_SANDSUPTOPRIGHT].x = 2 * 64;
			TileClips[TILE_SANDSUPTOPRIGHT].y = 2 * 48;
			TileClips[TILE_SANDSUPTOPRIGHT].w = TILE_WIDTH;
			TileClips[TILE_SANDSUPTOPRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_SANDSUPBOTLEFT].x = 2 * 48;
			TileClips[TILE_SANDSUPBOTLEFT].y = 2 * 64;
			TileClips[TILE_SANDSUPBOTLEFT].w = TILE_WIDTH;
			TileClips[TILE_SANDSUPBOTLEFT].h = TILE_HEIGHT;

			TileClips[TILE_SANDSUPBOTRIGHT].x = 2 * 64;
			TileClips[TILE_SANDSUPBOTRIGHT].y = 2 * 64;
			TileClips[TILE_SANDSUPBOTRIGHT].w = TILE_WIDTH;
			TileClips[TILE_SANDSUPBOTRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_SANDDECOR1].x = 2 * 80;
			TileClips[TILE_SANDDECOR1].y = 2 * 48;
			TileClips[TILE_SANDDECOR1].w = TILE_WIDTH;
			TileClips[TILE_SANDDECOR1].h = TILE_HEIGHT;

			TileClips[TILE_SANDDECOR2].x = 2 * 80;
			TileClips[TILE_SANDDECOR2].y = 2 * 64;
			TileClips[TILE_SANDDECOR2].w = TILE_WIDTH;
			TileClips[TILE_SANDDECOR2].h = TILE_HEIGHT;

			TileClips[TILE_SANDROCK1].x = 2 * 48;
			TileClips[TILE_SANDROCK1].y = 2 * 80;
			TileClips[TILE_SANDROCK1].w = TILE_WIDTH;
			TileClips[TILE_SANDROCK1].h = TILE_HEIGHT;

			TileClips[TILE_SANDROCK2].x = 2 * 64;
			TileClips[TILE_SANDROCK2].y = 2 * 80;
			TileClips[TILE_SANDROCK2].w = TILE_WIDTH;
			TileClips[TILE_SANDROCK2].h = TILE_HEIGHT;

			TileClips[TILE_SANDWOOD].x = 2 * 80;
			TileClips[TILE_SANDWOOD].y = 2 * 80;
			TileClips[TILE_SANDWOOD].w = TILE_WIDTH;
			TileClips[TILE_SANDWOOD].h = TILE_HEIGHT;

			//WATER
			TileClips[TILE_WATERTOPLEFT].x = 2 * 0;
			TileClips[TILE_WATERTOPLEFT].y = 2 * 96;
			TileClips[TILE_WATERTOPLEFT].w = TILE_WIDTH;
			TileClips[TILE_WATERTOPLEFT].h = TILE_HEIGHT;

			TileClips[TILE_WATERTOP].x = 2 * 16;
			TileClips[TILE_WATERTOP].y = 2 * 96;
			TileClips[TILE_WATERTOP].w = TILE_WIDTH;
			TileClips[TILE_WATERTOP].h = TILE_HEIGHT;

			TileClips[TILE_WATERTOPRIGHT].x = 2 * 32;
			TileClips[TILE_WATERTOPRIGHT].y = 2 * 96;
			TileClips[TILE_WATERTOPRIGHT].w = TILE_WIDTH;
			TileClips[TILE_WATERTOPRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_WATERLEFT].x = 2 * 0;
			TileClips[TILE_WATERLEFT].y = 2 * 112;
			TileClips[TILE_WATERLEFT].w = TILE_WIDTH;
			TileClips[TILE_WATERLEFT].h = TILE_HEIGHT;

			TileClips[TILE_WATERMIDDLE].x = 2 * 16;
			TileClips[TILE_WATERMIDDLE].y = 2 * 112;
			TileClips[TILE_WATERMIDDLE].w = TILE_WIDTH;
			TileClips[TILE_WATERMIDDLE].h = TILE_HEIGHT;

			TileClips[TILE_WATERRIGHT].x = 2 * 32;
			TileClips[TILE_WATERRIGHT].y = 2 * 112;
			TileClips[TILE_WATERRIGHT].w = TILE_WIDTH;
			TileClips[TILE_WATERRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_WATERBOTLEFT].x = 2 * 0;
			TileClips[TILE_WATERBOTLEFT].y = 2 * 128;
			TileClips[TILE_WATERBOTLEFT].w = TILE_WIDTH;
			TileClips[TILE_WATERBOTLEFT].h = TILE_HEIGHT;

			TileClips[TILE_WATERBOT].x = 2 * 16;
			TileClips[TILE_WATERBOT].y = 2 * 128;
			TileClips[TILE_WATERBOT].w = TILE_WIDTH;
			TileClips[TILE_WATERBOT].h = TILE_HEIGHT;

			TileClips[TILE_WATERBOTRIGHT].x = 2 * 32;
			TileClips[TILE_WATERBOTRIGHT].y = 2 * 128;
			TileClips[TILE_WATERBOTRIGHT].w = TILE_WIDTH;
			TileClips[TILE_WATERBOTRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_WATERSUPTOPLEFT].x = 2 * 48;
			TileClips[TILE_WATERSUPTOPLEFT].y = 2 * 48;
			TileClips[TILE_WATERSUPTOPLEFT].w = TILE_WIDTH;
			TileClips[TILE_WATERSUPTOPLEFT].h = TILE_HEIGHT;

			TileClips[TILE_WATERSUPTOPRIGHT].x = 2 * 64;
			TileClips[TILE_WATERSUPTOPRIGHT].y = 2 * 96;
			TileClips[TILE_WATERSUPTOPRIGHT].w = TILE_WIDTH;
			TileClips[TILE_WATERSUPTOPRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_WATERSUPBOTLEFT].x = 2 * 48;
			TileClips[TILE_WATERSUPBOTLEFT].y = 2 * 112;
			TileClips[TILE_WATERSUPBOTLEFT].w = TILE_WIDTH;
			TileClips[TILE_WATERSUPBOTLEFT].h = TILE_HEIGHT;

			TileClips[TILE_WATERSUPBOTRIGHT].x = 2 * 64;
			TileClips[TILE_WATERSUPBOTRIGHT].y = 2 * 112;
			TileClips[TILE_WATERSUPBOTRIGHT].w = TILE_WIDTH;
			TileClips[TILE_WATERSUPBOTRIGHT].h = TILE_HEIGHT;

			TileClips[TILE_WATERFLOWER1].x = 2 * 80;
			TileClips[TILE_WATERFLOWER1].y = 2 * 96;
			TileClips[TILE_WATERFLOWER1].w = TILE_WIDTH;
			TileClips[TILE_WATERFLOWER1].h = TILE_HEIGHT;

			TileClips[TILE_WATERFLOWER2].x = 2 * 80;
			TileClips[TILE_WATERFLOWER2].y = 2 * 112;
			TileClips[TILE_WATERFLOWER2].w = TILE_WIDTH;
			TileClips[TILE_WATERFLOWER2].h = TILE_HEIGHT;

			TileClips[TILE_WATERROCK1].x = 2 * 48;
			TileClips[TILE_WATERROCK1].y = 2 * 128;
			TileClips[TILE_WATERROCK1].w = TILE_WIDTH;
			TileClips[TILE_WATERROCK1].h = TILE_HEIGHT;

			TileClips[TILE_WATERROCK2].x = 2 * 64;
			TileClips[TILE_WATERROCK2].y = 2 * 128;
			TileClips[TILE_WATERROCK2].w = TILE_WIDTH;
			TileClips[TILE_WATERROCK2].h = TILE_HEIGHT;

			TileClips[TILE_WATERWOOD].x = 2 * 80;
			TileClips[TILE_WATERWOOD].y = 2 * 128;
			TileClips[TILE_WATERWOOD].w = TILE_WIDTH;
			TileClips[TILE_WATERWOOD].h = TILE_HEIGHT;

			TileClips[54] = { 0,0,0,0 };
		}
	}

	//Close the file
	csv.close();

	//If the map was loaded fine
	return tilesLoaded;
}