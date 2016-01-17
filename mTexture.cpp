#include "mTexture.h"
#include <SDL2/SDL.h>
#include <iostream>

mTexture::mTexture(SDL_Renderer* renderer)
{
	mWidth = 0;
	mHeight = 0;
	tex = NULL;
	ren = renderer;
}

mTexture::~mTexture()
{
	free();
}

bool mTexture::loadFromFile(std::string path)
{
	free();

	SDL_Texture* newTex = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		std::cout << "UNABLE TO LOAD IMAGE OH GOD PATH: " << path << IMG_GetError() << std::endl;
	}
	else {
		//Colour key?
		newTex = SDL_CreateTextureFromSurface(ren, loadedSurface);
		if (newTex == NULL) {
			std::cout << "UNABLE TO LOAD TEXTURE OH GOD PATH: " << path << IMG_GetError() << std::endl;
		}
		else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	tex = newTex;
	return tex!= NULL;
}

void mTexture::free()
{
	if (tex != NULL) {
		SDL_DestroyTexture(tex);
		tex = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void mTexture::render(int x, int y)
{
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	SDL_RenderCopy(ren, tex, NULL, &renderQuad);
}

int mTexture::getWidth()
{
	return mWidth;
}

int mTexture::getHeight()
{
	return mHeight;
}
