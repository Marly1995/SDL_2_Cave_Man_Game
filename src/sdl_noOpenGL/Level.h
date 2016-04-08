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

class Level
{
public:
	int world[12][12] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,1,1,1,2,1,1,0,0,0,0 },
		{ 0,0,0,0,0,2,0,0,0,0,0,0 },
		{ 0,0,1,1,1,1,2,0,0,0,0,0 },
		{ 0,0,0,0,0,0,2,0,0,0,0,0 },
		{ 0,0,0,0,1,1,1,1,1,2,0,0 },
		{ 0,0,0,0,0,0,0,0,0,2,0,0 },
		{ 0,1,1,2,1,0,1,1,2,1,1,0 },
		{ 0,0,0,2,0,0,0,0,2,0,0,0 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1 }
	};
};