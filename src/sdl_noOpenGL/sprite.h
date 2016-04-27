#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>

using namespace std;

class Sprite
{
public:
	std::string imagePath;
	SDL_Texture *Tex;
	SDL_Surface *surface;

	int xSpriteIndex;
	int ySpriteIndex;
	int spriteWidth;
	int spriteHeight;
	int displaySizeWidth;
	int displaySizeHeight;

	void loadSprite(string path, SDL_Renderer *ren);
};

void Sprite::loadSprite(string path, SDL_Renderer *ren)
{
	imagePath = path;
	surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n");
	}
	Tex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (Tex == nullptr) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n");
	}
}