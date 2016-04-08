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

class sprite
{
private:
	std::string imagePath;
	int xSpriteIndex;
	int ySpriteIndex;
	int spriteWidth;
	int spriteHeight;
	int displaySizeWidth;
	int displaySizeHeight;
};