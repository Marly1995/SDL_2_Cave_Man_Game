#pragma once
#include "player.h"
#include "sprite.h"
#include "Level.h"
#include "Enemy.h"
#include "Floor.h"
#include "Ladder.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <assert.h>

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_ttf.h>

using namespace std;

class Text
{
private:
	int width;
	int height;

public:
	SDL_Texture* textTex;
	SDL_Surface* textSurface;
	SDL_Renderer* ren;
	SDL_Rect textRect;
	TTF_Font* sans;
	SDL_Color White = { 255, 255, 255 };

public:
	void initText();
	Text(string input);
};

Text::Text(string input)
{
	initText();
	textSurface = TTF_RenderText_Solid(sans, input.c_str(), White);
	textTex = SDL_CreateTextureFromSurface(ren, textSurface);
}

void Text::initText()
{
	sans = TTF_OpenFont("assets/Hack-Regular.ttf", 96);
	//assert(sans != nullptr);
	if (sans == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
	}
}