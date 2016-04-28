#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "GameObject.h"
#include "sprite.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>

using namespace std;

class TextureControl
{
public:
	Sprite player;
	Sprite floor;
	Sprite ladder;
	Sprite background;
	Sprite pauseCover;
	Sprite bar;
	Sprite enemy;
	Sprite egg;
	Sprite menu;
	Sprite load;
};