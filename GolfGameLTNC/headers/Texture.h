#pragma once
#include <SDL_ttf.h>
//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

//#if defined(SDL_TTF_MAJOR_VERSION)
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *gFont);
//#endif

	//Creates blank texture
	bool createBlank(int width, int height, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING);

	//Deallocates texture
	void free();

	//Pass renderer
	void addRenderer(SDL_Renderer* renderer);

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Renders texture at given point
	void render(int x, int y, int w, int h, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	//Set self as render target
	void setAsRenderTarget();

	//Gets image dimensions
	int getWidth();
	int getHeight();

	//Pixel manipulators
	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	void copyPixels(void* pixels);
	int getPitch();
	Uint32 getPixel32(unsigned int x, unsigned int y);

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	void* mPixels;
	int mPitch;
	SDL_Renderer* gRenderer;
	//Image dimensions
	int mWidth;
	int mHeight;
};



